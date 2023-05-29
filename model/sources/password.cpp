//
// Created by Cezary Petryka on 14/05/2023.
//

#include "../password.hpp"

Password::Password(const std::string& name, const std::string& password, const std::string& category,
                   const std::optional<std::string>& websiteAddress, const std::optional<std::string>& login)
                   : description(name), password(password), category(category), website_address(websiteAddress),
                   login(login) {}

std::string Password::get_category() const noexcept {
    return category;
}

bool Password::is_password_the_same(const std::string &expression) const noexcept {
    return password == expression;
}

bool Password::check_match(const password_field &field, const std::string &value) const noexcept {
    if(field == password_field::DESCRIPTION) {
        return Utilities::contains_case_insensitive(description, value);
    }
    else if(field == password_field::PASSWORD) {
        return password == value;
    }
    else if(field == password_field::CATEGORY) {
        return category == value;
    }
    else if(field == password_field::WEBSITE_ADDRESS) {
        return Utilities::contains_case_insensitive(website_address.value_or(""), value);
    }
    else if(field == password_field::LOGIN) {
        return login.value_or("") == value;
    }
}

bool Password::edit_password(const password_field &field, const std::string &new_value) noexcept {
    switch (field) {
        case password_field::DESCRIPTION:
            description = new_value;
            break;
        case password_field::PASSWORD:
            if(!PasswordValidator::is_password_valid(new_value)) {
                return false;
            }

            password = new_value;
            break;
        case password_field::CATEGORY:
            category = new_value;
            break;
        case password_field::WEBSITE_ADDRESS:
            if(!PasswordValidator::is_website_address_valid(new_value)) {
                return false;
            }

            website_address = new_value;
            break;
        case password_field::LOGIN:
            login = new_value;
            break;
    }

    return true;
}

std::string Password::generate_password(const int length, const bool upper_and_lowercase, const bool special_characters) noexcept {
    // Create a string containing all the valid characters
    auto lowercase_letters = std::string("abcdefghijklmnopqrstuvwxyz");
    auto uppercase_letters = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    auto numbers = std::string("0123456789");
    auto special_chars = std::string("!@#$%^&*");

    auto valid_chars = lowercase_letters + numbers;

    if(upper_and_lowercase) {
        valid_chars += uppercase_letters;
    }

    if(special_characters) {
        valid_chars += numbers + special_chars;
    }

    // Generate a random password
    std::string password;

    for(int i = 0; i < length; i++) {
        password += valid_chars[rand() % valid_chars.size()];
    }

    return password;
}

password_strength Password::get_password_strength(const std::string &expression) noexcept {
    auto score {0};

    if(expression.size() < 8) {
        return password_strength::VERY_WEAK;
    }

    if(expression.size() >= 8) {
        score++;
    }

    if(Utilities::contains_any(expression, std::string("abcdefghijklmnopqrstuvwxyz"))) {
        score++;
    }

    if(Utilities::contains_any(expression, std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"))) {
        score++;
    }

    if(Utilities::contains_any(expression, std::string("0123456789"))) {
        score++;
    }

    if(Utilities::contains_any(expression, std::string("!@#$%^&*"))) {
        score++;
    }

    switch (score) {
        case 0:
        case 1:
            return password_strength::VERY_WEAK;
        case 2:
            return password_strength::WEAK;
        case 3:
            return password_strength::MEDIUM;
        case 4:
            return password_strength::STRONG;
        case 5:
            return password_strength::VERY_STRONG;
    }
}

std::string Password::get_raw_string(const std::string& separator) const noexcept {
    return description + separator
            + password + separator
            + category + separator
            + website_address.value_or("-") + separator
            + login.value_or("-");
}

std::ostream& operator<<(std::ostream& out, const Password& password) {
    return out << "PASSWORD{ DESCRIPTION: " << password.description << ", PASSWORD: " << password.password
               << ", CATEGORY: " << password.category << ", WEBSITE ADDRESS: " << password.website_address.value_or("-")
               << ", LOGIN: " << password.login.value_or("-") << " }";
}