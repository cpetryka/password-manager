//
// Created by Cezary Petryka on 16/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_PASSWORD_MANAGER_HPP

#include "../libs/libs.hpp"
#include "../model/password.hpp"
#include "../model/password_field.hpp"
#include "../model/password_strength.hpp"
#include "../validator/password_validator.hpp"
#include "../file/writer/file_writer.hpp"
#include "../encription/encryptor.hpp"
#include "../utilities/utilities.hpp"

/**
 * @brief Class representing a password manager
 * @details This class is used to manage passwords.
 */
class PasswordManager {
    fs::path path_to_file_with_passwords;
    std::string master_password;
    std::vector<std::unique_ptr<Password>> passwords;
    std::set<std::string> categories;

    /**
     * @brief Gets criteria (for sorting, filtering etc.) from user
     * @return std::vector<std::pair<password_field, std::string>> containing criteria
     */
    static std::vector<std::pair<password_field, std::string>> get_criteria_from_user() noexcept;

    /**
     * @brief Refreshes the set of categories
     */
    void refresh_categories_set() noexcept;

    /**
     * @brief Checks if the category exists
     * @param category
     * @return true if the category exists, false otherwise
     */
    bool do_category_exists(const std::string& category) const noexcept;

    /**
     * @brief Gets all categories as a string
     * @return std::string containing all categories
     */
    std::string get_categories_string() const noexcept;

    /**
     * @brief Checks if the password has already been used
     * @param std::filesystem::path path to the file with passwords
     * @param std::string containing the password
     * @return true if the password has already been used, false otherwise
     */
    bool check_if_password_has_already_been_used(const std::string& password) const noexcept;

    /**
     * @brief Generates a vector of strings that will be saved to the file
     */
    std::vector<std::string> generate_decrypted_output_vector() const noexcept;
public:
    explicit PasswordManager(const fs::path& path_to_file_with_passwords, const std::string& master_password, const std::vector<std::unique_ptr<Password>>& passwords) noexcept;

    PasswordManager(const PasswordManager& pm) noexcept;
    PasswordManager(PasswordManager&& pm) noexcept;

    PasswordManager& operator=(const PasswordManager& pm);
    PasswordManager& operator=(PasswordManager&& pm) noexcept;

    /**
     * @brief Returns passwords that match the given criteria
     * @return std::vector<std::unique_ptr<Password>> containing passwords that match the given criteria
     */
    std::vector<std::unique_ptr<Password>> get_passwords() noexcept;

    /**
     * @brief Adds a new password
     */
    void add_password_menu() noexcept;

    /**
     * @brief Allows the user to edit the selected password
     */
    void edit_password_menu() noexcept;

    /**
     * @brief Removes passwords chosen by the user
     * @details Shows all passwords and asks the user which passwords should be removed
     */
    void remove_passwords_menu();

    /**
     * @brief Removes passwords at given indexes
     * @param indexes vector of indexes of passwords to be removed
     */
    void remove_passwords_at_indexes(std::vector<int>& indexes);

    /**
     * @brief Adds a new category
     */
    void add_category_menu() noexcept;

    /**
     * @brief Removes a category and all passwords that belong to it
     */
    void remove_category_menu() noexcept;

    /**
     * @brief Shows a menu for the user
     * @details The user can choose what to do with the passwords (e.g. sort, filter, add, remove etc.)
     */
    void menu() noexcept;

    friend std::ostream& operator<<(std::ostream& out, const PasswordManager& pm) noexcept;
};


#endif //PASSWORD_MANAGER_PASSWORD_MANAGER_HPP
