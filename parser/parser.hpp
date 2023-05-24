//
// Created by Cezary Petryka on 24/05/2023.
//

#ifndef PASSWORD_MANAGER_PARSER_HPP
#define PASSWORD_MANAGER_PARSER_HPP

#include "../libs/libs.hpp"

// T - output type
template<typename T>
struct Parser {
    Parser() = default;

    virtual T parse(const std::string& expression) = 0;

    virtual ~Parser() = default;
};


#endif //PASSWORD_MANAGER_PARSER_HPP
