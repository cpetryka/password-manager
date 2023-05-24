//
// Created by Cezary Petryka on 23/05/2023.
//

#ifndef PASSWORD_MANAGER_VALIDATOR_HPP
#define PASSWORD_MANAGER_VALIDATOR_HPP

#include "../libs/libs.hpp"

/**
 * @brief Abstract class for validators
 */
struct Validator {
    Validator() = default;

    /**
     * @brief Checks if expression passed as an argument is valid
     * @param std::string representing some expression
     * @return true if expression is valid, false otherwise
     */
    virtual bool validate(const std::string& expression) const = 0;

    virtual ~Validator() = default;
};

#endif //PASSWORD_MANAGER_VALIDATOR_HPP
