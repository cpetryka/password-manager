//
// Created by Cezary Petryka on 18/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_VALIDATOR_HPP
#define PASSWORD_MANAGER_PASSWORD_VALIDATOR_HPP

#include "../libs/libs.hpp"

/**
 * @brief Validator for strings representing password
 */
struct PasswordValidator {
    /**
     * @brief Checks if expression passed as an argument is a valid password
     * @param std::string representing password
     * @return true if expression is a valid password, false otherwise
     */
    static bool validate(const std::string &expression) {
        return std::regex_match(expression, std::regex(".+;.{8,30};[a-z]+;(-|www\\..+\\.(pl|com|org));(-|.+)"));
    }
};

#endif //PASSWORD_MANAGER_PASSWORD_VALIDATOR_HPP