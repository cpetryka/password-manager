//
// Created by Cezary Petryka on 14/05/2023.
//

#include "../password.hpp"

Password::Password(const std::string& name, const std::string& password, const std::string& category,
                   const std::optional<std::string>& websiteAddress, const std::optional<std::string>& login)
                   : description(name), password(password), category(category), website_address(websiteAddress),
                   login(login) {}

std::ostream& operator<<(std::ostream& out, const Password& password) {
    return out << "PASSWORD{ DESCRIPTION: " << password.description << ", PASSWORD: " << password.password
               << ", CATEGORY: " << password.category << ", WEBSITE ADDRESS: " << password.website_address.value_or("-")
               << ", LOGIN: " << password.login.value_or("-") << " }";
}
