//
// Created by Cezary Petryka on 26/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_FIELD_HPP
#define PASSWORD_MANAGER_PASSWORD_FIELD_HPP

#include "../libs/libs.hpp"

/**
 * @brief Namespace containing all possible password fields
 * @details The enum from this namespace is used in the PasswordManager class to choose a field to search for, sort by, etc.
 */
namespace PasswordField {
    enum class Type {
        DESCRIPTION,
        PASSWORD,
        CATEGORY,
        WEBSITE_ADDRESS,
        LOGIN
    };

    static Type Types[] = {
            Type::DESCRIPTION,
            Type::PASSWORD,
            Type::CATEGORY,
            Type::WEBSITE_ADDRESS,
            Type::LOGIN
    };
    static int SIZE = 5;

    /**
     * @brief Function used to convert a "field" to a string
     * @param type "Field" to convert to a string
     * @return std::string containing the "field" name
     */
    static std::string to_string(const Type& type) {
        std::vector<std::string> strings = {
                "description",
                "password",
                "category",
                "website_address",
                "login"
        };
        return strings[static_cast<int>(type)];
    }

    /**
     * @brief Function used to get a "field" at the given index
     * @param idx Index of the "field"
     * @return "Field" at the given index
     */
    static Type at_idx(const int idx) {
        if(idx < 0 || idx >= SIZE) {
            throw std::out_of_range{"Index out of range"};
        }

        return Types[idx];
    }

    /**
     * @brief Function used to choose a "field" from the shown menu
     * @return Chosen "field"
     */
    static Type choose_field_menu() {
        std::cout << "Choose one of the following fields:" << std::endl;

        for(int i = 0; i < SIZE; i++) {
            std::cout << i + 1 << ". " << to_string(at_idx(i)) << std::endl;
        }

        std::cout << "Your choice: ";
        auto choice {-1};
        std::cin >> choice; std::cin.get();

        return at_idx(choice - 1);
    }
}

using password_field = PasswordField::Type;

#endif //PASSWORD_MANAGER_PASSWORD_FIELD_HPP
