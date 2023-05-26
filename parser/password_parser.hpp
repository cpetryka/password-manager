//
// Created by Cezary Petryka on 24/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_PARSER_HPP
#define PASSWORD_MANAGER_PASSWORD_PARSER_HPP

#include "../model/password.hpp"
#include "../validator/password_validator.hpp"
#include "../utilities/utilities.hpp"

/**
 * @brief Class for parsing passwords
 */
struct PasswordParser {
    /**
     * @brief Parses an expression passed as an argument
     * @param std::string representing some expression
     * @param std::string representing a separator
     * @return Password which is the generic type specified earlier
     */
    static Password parse(const std::string& expression, const std::string& separator) {
        auto split = Utilities::split(expression, separator);
        return Password{split[0], split[1], split[2], split[3], split[4]};
    }
};

#endif //PASSWORD_MANAGER_PASSWORD_PARSER_HPP
