//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_ENCRYPTOR_HPP
#define PASSWORD_MANAGER_ENCRYPTOR_HPP

#include "../libs/libs.hpp"

struct Encryptor {
    explicit Encryptor() = default;

    static std::string encrypt(const std::string& expression, const std::string& password);

    static std::string decrypt(const std::string& expression, const std::string& password);
    static std::vector<std::string> decrypt_all(const std::vector<std::string>& expressions, const std::string& password);
};

#endif //PASSWORD_MANAGER_ENCRYPTOR_HPP
