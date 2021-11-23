//
// Created by stephen on 10/29/21.
//

#ifndef HASHING_H
#define HASHING_H

#define OPENSSL_API_COMPAT 0x10100000L

#include <optional>
#include <string>

#include <openssl/evp.h>
#include <openssl/sha.h>

#define SHA256_LENGTH 32

namespace MHV
{
    class Hashing
    {
        public:
            Hashing();
            ~Hashing();

            std::optional<std::pair<std::string,std::string>> encryptPassword(std::string password);
            bool validatePassword(std::string pw, std::string hash, std::string salt);

        private:
            void calcSHA256(std::string str);
            std::string getSalt();

        private:
            unsigned char _hash[SHA256_LENGTH];
            SHA256_CTX _context;
            const std::string _pepper;
    };
}

#endif // HASHING_H
