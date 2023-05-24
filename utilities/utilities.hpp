//
// Created by Cezary Petryka on 24/05/2023.
//

#ifndef PASSWORD_MANAGER_UTILITIES_HPP
#define PASSWORD_MANAGER_UTILITIES_HPP

#include "../libs/libs.hpp"

/**
 * @brief Class with some useful methods
 */
struct Utilities {
    Utilities();

    /**
     * @brief Splits expression by specified delimiter
     * @param std::string representing some expression
     * @param std::string representing delimiter
     * @return std::vector<std::string> containing split expressions
     */
    static std::vector<std::string> split(const std::string& expression, const std::string& delimiter);
};


#endif //PASSWORD_MANAGER_UTILITIES_HPP
