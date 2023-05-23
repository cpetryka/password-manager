//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_ENCRYPTOR_HPP
#define PASSWORD_MANAGER_ENCRYPTOR_HPP

#include "../libs/libs.hpp"

class Encryptor {
    std::string seed;
public:
    explicit Encryptor(const std::string& encryption_seed);

    std::string encrypt(const std::string& expression) const;

    std::string decrypt(const std::string& expression) const;
};

#endif //PASSWORD_MANAGER_ENCRYPTOR_HPP
