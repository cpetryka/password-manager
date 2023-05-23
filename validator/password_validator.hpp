//
// Created by Cezary Petryka on 18/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_VALIDATOR_HPP
#define PASSWORD_MANAGER_PASSWORD_VALIDATOR_HPP

#include "validator.hpp"

class PasswordValidator : public Validator {
    // The required format of the password record is:
    // Name can be any string
    // Password may contain any characters and its length must be between 8 and 30 characters
    // Category can contain only lowercase letters
    // Address is optional, but if it is used it must be in the format www.address.X, where X is pl, com or org
    // Login is optional and if it is used it can be any string
    static const std::regex PASSWORD_REGEX;

public:
    bool validate(const std::string &expression) const override {
        return std::regex_match(expression, PASSWORD_REGEX);
    }
};

const std::regex PasswordValidator::PASSWORD_REGEX = std::regex(".+;.{8,30};[a-z]+;(-|www\\..+\\.(pl|com|org));(-|.+)");

#endif //PASSWORD_MANAGER_PASSWORD_VALIDATOR_HPP
