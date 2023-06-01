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
     * @param std::string representing some expression
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

    /**
     * @brief Prints message, asks user yes or no question and returns the answer as bool
     * @param message
     * @return true if user answered yes, false otherwise
     */
    static bool get_yes_or_no_from_user(const std::string& message);

    /**
     * @brief Adds front zeros to number
     * @param number
     * @param full_length
     * @return std::string containing number with front zeros
     */
    static std::string add_front_zeros(int number, const int full_length);

    /**
     * @brief Gets current date and time as string
     * @return std::string containing current date and time
     * @details Format: YYYYMMDDHHMMSS
     */
    static std::string get_current_date_and_time_as_raw_string();

    /**
     * @brief Converts raw date string to standard format
     * @param std::string containing raw date string
     * @return std::string containing date in standard format (YYYY-MM-DD HH:MM:SS)
     */
    static std::string convert_raw_date_string_to_standard_format(const std::string& raw_date_string);
};


#endif //PASSWORD_MANAGER_UTILITIES_HPP
