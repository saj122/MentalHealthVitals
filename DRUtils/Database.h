//
// Created by stephen on 10/28/21.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <optional>

#include "Patient.h"

class sqlite3;

namespace MHV
{
    class Database
    {
        public:
            Database();
            ~Database();
            std::optional<std::string> registerUser(const Patient& user);
            bool registerPassword(std::string id, std::string password, std::string salt);
            std::optional<std::string> lookUpUser(std::string user);
            std::optional<std::pair<std::string, std::string>> getHashAndSalt(std::string user);
        private:
            static int exec_callback(void* data, int argc, char** argv, char** azColName);
        private:
            sqlite3* _db;
            char* _msgError;
    };
}


#endif //DATABASE_H
