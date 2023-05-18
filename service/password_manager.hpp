//
// Created by Cezary Petryka on 16/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_PASSWORD_MANAGER_HPP

#include "../libs/libs.hpp"
#include "../model/password.hpp"

class PasswordManager {
    std::vector<Password> passwords;
public:
    PasswordManager();
};


#endif //PASSWORD_MANAGER_PASSWORD_MANAGER_HPP
