//
// Created by Cezary Petryka on 16/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_PASSWORD_MANAGER_HPP

#include "../libs/libs.hpp"
#include "../model/password.hpp"

/**
 * @brief Class representing a password manager
 * @details This class is used to manage passwords.
 */
class PasswordManager {
    std::vector<std::unique_ptr<Password>> passwords;
public:
    PasswordManager(const std::vector<std::unique_ptr<Password>>& passwords) noexcept;

    PasswordManager(const PasswordManager& pm) noexcept;
    PasswordManager(PasswordManager&& pm) noexcept;

    PasswordManager& operator=(const PasswordManager& pm);
    PasswordManager& operator=(PasswordManager&& pm) noexcept;

    friend std::ostream& operator<<(std::ostream& out, const PasswordManager& pm) noexcept {
        std::ranges::for_each(pm.passwords, [&out](const auto& password) {
            out << *password << '\n';
        });

        return out;
    }
};


#endif //PASSWORD_MANAGER_PASSWORD_MANAGER_HPP
