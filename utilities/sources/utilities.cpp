//
// Created by Cezary Petryka on 24/05/2023.
//

#include "../utilities.hpp"

Utilities::Utilities() {
    throw std::runtime_error("This class is not supposed to be instantiated");
}

std::vector<std::string> Utilities::split(const std::string& expression, const std::string& delimiter) {
    std::stringstream ss(expression);
    std::string token;

    std::vector<std::string> result;

    while(std::getline(ss, token, delimiter[0])) {
        result.emplace_back(token);
    }

    return result;
}
