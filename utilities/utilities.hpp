//
// Created by Cezary Petryka on 24/05/2023.
//

#ifndef PASSWORD_MANAGER_UTILITIES_HPP
#define PASSWORD_MANAGER_UTILITIES_HPP

#include "../libs/libs.hpp"

struct Utilities {
    Utilities();

    static std::vector<std::string> split(const std::string& expression, const std::string& delimiter);
};


#endif //PASSWORD_MANAGER_UTILITIES_HPP
