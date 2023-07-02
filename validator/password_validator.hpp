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

    /**
     * @brief Checks if expression passed as an argument is a valid password (not all password-related information, but strictly the password to some service)
     * @param std::string representing password
     * @return true if expression is a valid password, false otherwise
     */
    static bool is_password_valid(const std::string& expression) {
        return std::regex_match(expression, std::regex(".{8,30}"));
    }

    /**
     * @brief Checks if expression passed as an argument is a valid website address
     * @param std::string representing website address
     * @return true if expression is a valid website address, false otherwise
     */
    static bool is_website_address_valid(const std::string& expression) {
        return std::regex_match(expression, std::regex("(-|www\\..+\\.(pl|com|org))"));
    }
};

#endif //PASSWORD_MANAGER_PASSWORD_VALIDATOR_HPP