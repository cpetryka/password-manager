//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_HPP
#define PASSWORD_MANAGER_PASSWORD_HPP

#include "password_field.hpp"
#include "../validator/password_validator.hpp"
#include "../model/password_strength.hpp"
#include "../utilities/utilities.hpp"

/**
 * @brief Class representing a password
 * @details This class is used in the PasswordManager class to store (and manage) passwords.
 */
class Password {
    std::string description;
    std::string password;
    std::string category;
    std::optional<std::string> website_address;
    std::optional<std::string> login;
public:
    Password(const std::string &name, const std::string &password, const std::string &category,
             const std::optional<std::string> &websiteAddress, const std::optional<std::string> &login);

    /**
     * @brief Gets the specified field of the password
     * @param field
     * @return the specified field of the password
     */
    std::string get_field(const password_field& field) const noexcept;

    /**
     * @brief Checks if the password is the same as the given expression
     * @param expression
     * @return true if the password is the same as the given expression, false otherwise
     */
    bool is_password_the_same(const std::string& expression) const noexcept;

    /**
     * @brief Checks if the password matches the given criteria
     * @param field
     * @param value
     * @return true if the password matches the given criteria, false otherwise
     */
    bool check_match(const password_field& field, const std::string& value) const noexcept;

    /**
     * @brief Edits the specified field of the password
     * @param field field to be edited
     * @param new_value new value of the field
     * @return true if the field was edited successfully, false otherwise
     */
    bool edit_password(const password_field& field, const std::string& new_value) noexcept;

    /**
     * @brief Generates a random password
     * @param length
     * @param upper_and_lowercase
     * @param special_characters
     * @return a random password
     */
    static std::string generate_password(const int length, const bool upper_and_lowercase, const bool special_characters) noexcept;

    /**
     * @brief Gets the strength of the password
     * @param std::string containing the password
     * @return password_strength enum
     */
    static password_strength get_password_strength(const std::string& expression) noexcept;

    std::string get_raw_string(const std::string& separator) const noexcept;

    friend std::ostream& operator<<(std::ostream& out, const Password& password);
};


#endif //PASSWORD_MANAGER_PASSWORD_HPP
