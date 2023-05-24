//
// Created by Cezary Petryka on 24/05/2023.
//

#ifndef PASSWORD_MANAGER_PARSER_HPP
#define PASSWORD_MANAGER_PARSER_HPP

#include "../libs/libs.hpp"

/**
 * @brief Abstract class for parsers
 * @tparam T which is output type
 */
template<typename T>
struct Parser {
    Parser() = default;

    /**
     * @brief Parses expression passed as an argument
     * @param std::string representing some expression
     * @return T which is the output type
     */
    virtual T parse(const std::string& expression) = 0;

    virtual ~Parser() = default;
};


#endif //PASSWORD_MANAGER_PARSER_HPP
