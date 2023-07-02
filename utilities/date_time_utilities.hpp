//
// Created by Cezary Petryka on 02/07/2023.
//

#ifndef PASSWORD_MANAGER_DATE_TIME_UTILITIES_HPP
#define PASSWORD_MANAGER_DATE_TIME_UTILITIES_HPP

#include "utilities.hpp"

/**
 * @brief Class with some useful methods to manage date and time
 */
struct DateTimeUtilities {
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


#endif //PASSWORD_MANAGER_DATE_TIME_UTILITIES_HPP
