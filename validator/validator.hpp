//
// Created by Cezary Petryka on 23/05/2023.
//

#ifndef PASSWORD_MANAGER_VALIDATOR_HPP
#define PASSWORD_MANAGER_VALIDATOR_HPP

#include "../libs/libs.hpp"

struct Validator {
    Validator() = default;

    virtual bool validate(const std::string& expression) const = 0;

    virtual ~Validator() = default;
};

#endif //PASSWORD_MANAGER_VALIDATOR_HPP
