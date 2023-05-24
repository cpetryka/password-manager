//
// Created by Cezary Petryka on 24/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_PARSER_HPP
#define PASSWORD_MANAGER_PASSWORD_PARSER_HPP

#include "parser.hpp"
#include "../model/password.hpp"
#include "../validator/password_validator.hpp"
#include "../utilities/utilities.hpp"

struct PasswordParser : Parser<std::unique_ptr<Password>> {
    std::unique_ptr<Password> parse(const std::string& expression) override {
        auto split = Utilities::split(expression, ";");
        return std::make_unique<Password>(split[0], split[1], split[2], split[3], split[4]);
    }
};

#endif //PASSWORD_MANAGER_PASSWORD_PARSER_HPP
