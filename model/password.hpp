//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_HPP
#define PASSWORD_MANAGER_PASSWORD_HPP

#include <ostream>
#include "../libs/libs.hpp"

// It's a class that represents a password and its data (description, category etc.)
// This class is used in the PasswordManager class to store (and manage) passwords.
class Password {
    std::string description;
    std::string password;
    // TODO: use enum
    std::string category;
    std::optional<std::string> website_address;
    std::optional<std::string> login;
public:
    Password(const std::string &name, const std::string &password, const std::string &category,
             const std::optional<std::string> &websiteAddress, const std::optional<std::string> &login);

    friend std::ostream& operator<<(std::ostream& out, const Password& password);
};


#endif //PASSWORD_MANAGER_PASSWORD_HPP
