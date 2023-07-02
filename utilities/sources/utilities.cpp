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