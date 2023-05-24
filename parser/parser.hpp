//
// Created by Cezary Petryka on 24/05/2023.
//

#ifndef PASSWORD_MANAGER_PARSER_HPP
#define PASSWORD_MANAGER_PARSER_HPP

#include "../libs/libs.hpp"

// T - output type
template<typename T>
struct Parser {
    virtual T parse(const std::string& expression) = 0;
};


#endif //PASSWORD_MANAGER_PARSER_HPP
