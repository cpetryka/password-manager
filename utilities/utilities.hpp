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

    /**
     * @brief Splits expression by specified delimiter and converts it to numbers
     * @param std::string representing some expression
     * @param std::string representing delimiter
     * @return std::vector<int> containing split expressions converted to numbers
     */
    static std::vector<int> split_to_numbers(const std::string& expression, const std::string& delimiter);

    /**
     * @brief Converts expression to lowercase
     * @param expression
     * @return std::string containing expression in lowercase
     */
    static std::string to_lowercase(const std::string& expression);

    /**
     * @brief Checks if expression contains at least one character from the given substring
     * @param expression
     * @param substring
     * @return true if expression contains at least one character from the given substring, false otherwise
     */
    static bool contains_any(const std::string& expression, const std::string& substring);

    /**
     * @brief Checks if expression contains substring (case insensitive)
     * @param expression
     * @param substring
     * @return true if expression contains substring, false otherwise
     */
    static bool contains_case_insensitive(const std::string& expression, const std::string& substring);
};


#endif //PASSWORD_MANAGER_UTILITIES_HPP
