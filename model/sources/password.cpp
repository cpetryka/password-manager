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
            if(!PasswordValidator::is_valid_password(new_value)) {
                return false;
            }

            password = new_value;
            break;
        case password_field::CATEGORY:
            category = new_value;
            break;
        case password_field::WEBSITE_ADDRESS:
            if(!PasswordValidator::is_valid_website_address(new_value)) {
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

std::ostream& operator<<(std::ostream& out, const Password& password) {
    return out << "PASSWORD{ DESCRIPTION: " << password.description << ", PASSWORD: " << password.password
               << ", CATEGORY: " << password.category << ", WEBSITE ADDRESS: " << password.website_address.value_or("-")
               << ", LOGIN: " << password.login.value_or("-") << " }";
}