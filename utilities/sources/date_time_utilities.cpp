//
// Created by Cezary Petryka on 02/07/2023.
//

#include "../date_time_utilities.hpp"

std::string DateTimeUtilities::get_current_date_and_time_as_raw_string() {
    const std::chrono::time_point now{std::chrono::system_clock::now()};
    const std::chrono::zoned_time zt{std::chrono::current_zone(), now};

    // We need to get only first 14 characters, because we don't need precise milliseconds
    // We also need to add "00" at the end as the primitive representation of milliseconds
    return std::format("{:%Y%m%d%H%M%S}", zt).substr(0, 14) + "00";
}

std::string DateTimeUtilities::convert_raw_date_string_to_standard_format(const std::string &raw_date_string) {
    std::string result = raw_date_string;

    result.insert(4, "-");
    result.insert(7, "-");
    result.insert(10, " ");
    result.insert(13, ":");
    result.insert(16, ":");
    result.erase(result.size() - 2);

    return result;
}
