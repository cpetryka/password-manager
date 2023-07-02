//
// Created by Cezary Petryka on 02/07/2023.
//

#include "../date_time_utilities.hpp"

std::string DateTimeUtilities::get_current_date_and_time_as_raw_string() {
    const std::chrono::time_point now{std::chrono::system_clock::now()};
    const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
    const std::chrono::hh_mm_ss hms{std::chrono::floor<std::chrono::seconds>(now - std::chrono::floor<std::chrono::days>(now))};

    std::stringstream ss{};

    ss << ymd.year()
       << Utilities::add_front_zeros(static_cast<unsigned>(ymd.month()), 2)
       << Utilities::add_front_zeros(static_cast<unsigned>(ymd.day()), 2)
       << Utilities::add_front_zeros(hms.hours().count() + 2, 2)
       << Utilities::add_front_zeros(hms.minutes().count() , 2)
       << Utilities::add_front_zeros(hms.seconds().count() , 2) << "00";

    return ss.str();
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
