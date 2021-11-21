//
// Created by stephen on 10/28/21.
//

#include "Database.h"

#include <sqlite3.h>

#include <uuid/uuid.h>

#include <glog/logging.h>

MHV::Database::Database() : _db(nullptr),
                            _msgError(nullptr)
{
    if (sqlite3_open("MHV", &_db) != SQLITE_OK)
    {
        LOG(ERROR) << "Error opening database: " << sqlite3_errmsg(_db);
    }

    std::string createUserTable = "CREATE TABLE IF NOT EXISTS USERS(" \
                                  "ID                   CHAR(100)        NOT NULL," \
                                  "FIRSTNAME            TEXT             NOT NULL," \
                                  "LASTNAME             TEXT             NOT NULL," \
                                  "AGE                  TEXT             NOT NULL," \
                                  "USERNAME             TEXT             NOT NULL," \
                                  "EMAIL                TEXT             NOT NULL," \
                                  "AREACODE             TEXT             NOT NULL," \
                                  "PHONENUMBER          TEXT             NOT NULL," \
                                  "ADDRESS              TEXT             NOT NULL," \
                                  "OTHER                TEXT             NOT NULL," \
                                  "CITY                 TEXT             NOT NULL," \
                                  "STATE                TEXT             NOT NULL," \
                                  "ZIPCODE              TEXT             NOT NULL" \
                                  ");";

    if(sqlite3_exec(_db, createUserTable.c_str(), NULL, 0, &_msgError) != SQLITE_OK)
    {
        LOG(ERROR) << "Error creating table - " << _msgError;
    }

    std::string createAuthTable = "CREATE TABLE IF NOT EXISTS AUTH(" \
                                  "ID                   CHAR(100)        NOT NULL," \
                                  "HASH                 TEXT             NOT NULL," \
                                  "USERID               TEXT             NOT NULL," \
                                  "SALT                 TEXT             NOT NULL" \
                                  ");";

    if(sqlite3_exec(_db, createAuthTable.c_str(), NULL, 0, &_msgError) != SQLITE_OK)
    {
        LOG(ERROR) << "Error creating table - " << _msgError;
    }
}

MHV::Database::~Database()
{
    sqlite3_free(_msgError);
    sqlite3_close(_db);
}

int MHV::Database::exec_callback(void* data, int argc, char** argv, char** azColName)
{
    for(int i = 0; i < argc;i++)
    {
        LOG(INFO) << azColName[i] << "," << argv[i];
    }

    return 0;
}

std::optional<std::string> MHV::Database::registerUser(const Patient& user)
{
    std::string insertUserIntoTable = "INSERT INTO USERS VALUES(";

    uuid_t id;
    uuid_generate(id);
    char* guid = new char[100];
    uuid_unparse(id, guid);

    insertUserIntoTable.append("'");
    insertUserIntoTable.append(std::string(guid));
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.firstName);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.lastName);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.age);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.username);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.email);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.areaCode);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.phoneNumber);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.address);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.other);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.city);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.state);
    insertUserIntoTable.append("','");
    insertUserIntoTable.append(user.zipCode);
    insertUserIntoTable.append("');");

    if(sqlite3_exec(_db, insertUserIntoTable.c_str(), NULL, 0, &_msgError) != SQLITE_OK)
    {
        LOG(INFO) << "Failed to insert user.";
        return std::nullopt;
    }

    return guid;
}

bool MHV::Database::registerPassword(std::string id, std::string password, std::string salt)
{
    std::string insertPWIntoTable = "INSERT INTO AUTH VALUES(";

    uuid_t uuid;
    uuid_generate(uuid);
    char* guid = new char[100];
    uuid_unparse(uuid, guid);

    insertPWIntoTable.append("'");
    insertPWIntoTable.append(std::string(guid));
    insertPWIntoTable.append("','");
    insertPWIntoTable.append(password);
    insertPWIntoTable.append("','");
    insertPWIntoTable.append(id);
    insertPWIntoTable.append("','");
    insertPWIntoTable.append(salt);
    insertPWIntoTable.append("');");

    if(sqlite3_exec(_db, insertPWIntoTable.c_str(), NULL, 0, &_msgError) != SQLITE_OK)
    {
        LOG(INFO) << "Failed to insert hash.";
        return false;
    }
    return true;
}

std::optional<std::string> MHV::Database::lookUpUser(std::string user)
{
    std::string checkUserInTable = "SELECT USERNAME FROM USERS WHERE USERNAME=";
    checkUserInTable.append("'");
    checkUserInTable.append(user.c_str());
    checkUserInTable.append("';");
    if(sqlite3_exec(_db, checkUserInTable.c_str(), exec_callback, 0, &_msgError) != SQLITE_OK)
    {
        LOG(INFO) << "User not found.";
        return std::nullopt;
    }

    return user;
}

std::optional<std::pair<std::string, std::string>> MHV::Database::getHashAndSalt(std::string user)
{
    return std::nullopt;
}
