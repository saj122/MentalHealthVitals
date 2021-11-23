//
// Created by stephen on 10/29/21.
//

#include "Hashing.h"

#include <glog/logging.h>
#include <iomanip>

MHV::Hashing::Hashing() : _pepper("f1845c3c44410ec3b98a1ca5ccda581672f2f673e1dbd21c8db482ef8f429551")
{
    if(!SHA256_Init(&_context))
    {
        LOG(ERROR) << "Failed to create SHA 256 context.";
        return;
    }
}

MHV::Hashing::~Hashing()
{

}

void MHV::Hashing::calcSHA256(std::string str)
{
    if(!SHA256_Update(&_context, str.c_str(), str.length()))
    {
        LOG(ERROR) << "Failed to update SHA 256.";
        return;
    }

    if(!SHA256_Final(_hash, &_context))
    {
        LOG(ERROR) << "Failed to finalize SHA 256.";
        return;
    }
}

std::string MHV::Hashing::getSalt()
{
    std::stringstream shastr;
    shastr << std::hex << std::setfill('0');
    for(const auto &byte: _hash)
    {
        shastr << std::setw(2) << (int)byte;
    }
    return shastr.str();
}

std::optional<std::pair<std::string,std::string>> MHV::Hashing::encryptPassword(std::string password)
{
    unsigned char key[32] = {0};

    calcSHA256(password);
    std::string salt = getSalt();
    password.append(_pepper);
    if(!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), (const unsigned char*)salt.c_str(), salt.length(), 1007, EVP_sha256(), sizeof(key), key))
    {
        LOG(ERROR) << "Failed to generate key.";
        return std::nullopt;
    }

    std::pair<std::string,std::string> pair;
    pair.first = salt;
    pair.second = reinterpret_cast< char const* >(key);

    return pair;
}

bool MHV::Hashing::validatePassword(std::string pw, std::string hash, std::string salt)
{
    unsigned char key[32] = {0};
    pw.append(_pepper);
    if(!PKCS5_PBKDF2_HMAC(pw.c_str(), pw.length(), (const unsigned char*)salt.c_str(), salt.length(), 1007, EVP_sha256(), sizeof(key), key))
    {
        LOG(ERROR) << "Failed to generate key.";
        return false;
    }

    if(*hash.c_str() == *key)
    {
        return true;
    }
    else
    {
        return false;
    }
}