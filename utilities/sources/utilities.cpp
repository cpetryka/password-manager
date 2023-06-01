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

std::vector<int> Utilities::split_to_numbers(const std::string &expression, const std::string &delimiter) {
    auto split = Utilities::split(expression, delimiter);
    std::vector<int> result;
    std::ranges::transform(split, std::back_inserter(result), [](const auto& elem) {
        return std::stoi(elem);
    });
    return result;
}

std::string Utilities::to_lowercase(const std::string &expression) {
    auto expr = expression;
    std::ranges::transform(expr, expr.begin(), ::tolower);
    return expr;
}

bool Utilities::contains_any(const std::string &expression, const std::string &substring) {
    return std::ranges::any_of(expression, [&substring](const auto& elem) {
        return substring.find(elem) != std::string::npos;
    });
}

bool Utilities::contains_case_insensitive(const std::string &expression, const std::string &substring) {
    auto expr = Utilities::to_lowercase(expression);
    auto sub = Utilities::to_lowercase(substring);

    return expr.find(sub) != std::string::npos;
}

bool Utilities::get_yes_or_no_from_user(const std::string &message) {
    std::cout << message << " (y/n): ";
    std::string answer;
    std::getline(std::cin, answer);

    while(answer != "y" && answer != "n") {
        std::cout << "Wrong answer. Try again (y/n): ";
        std::getline(std::cin, answer);
    }

    return answer == "y";
}

std::string Utilities::add_front_zeros(int number, const int full_length) {
    std::string result = std::to_string(number);

    while(result.size() < full_length) {
        result = "0" + result;
    }

    return result;
}

std::string Utilities::get_current_date_and_time_as_raw_string() {
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

std::string Utilities::convert_raw_date_string_to_standard_format(const std::string &raw_date_string) {
    std::string result = raw_date_string;

    result.insert(4, "-");
    result.insert(7, "-");
    result.insert(10, " ");
    result.insert(13, ":");
    result.insert(16, ":");
    result.erase(result.size() - 2);

    return result;
}
