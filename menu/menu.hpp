//
// Created by Cezary Petryka on 26/05/2023.
//

#ifndef PASSWORD_MANAGER_MENU_HPP
#define PASSWORD_MANAGER_MENU_HPP

#include "../libs/libs.hpp"
#include "../file/manager/file_manager.hpp"
#include "../file/reader/file_reader.hpp"
#include "../file/writer/file_writer.hpp"
#include "../encription/encryptor.hpp"
#include "../validator/password_validator.hpp"

/**
 * @brief Class representing a menu
 * @details The class contains several static methods that are used to display the menu and get the user's input.
 */
struct Menu {
    /**
     * @brief This method allows user to choose whether to use one of the saved files or to provide their own path
     * @param std::filesystem::path representing a path to a directory with files with saved passwords
     * @return std::filesystem::path representing a path to a chosen file
     */
    static fs::path get_path_to_file_with_passwords_from_user(const fs::path& path_to_files_with_saved_passwords);

    /**
     * @brief This method allows user to enter a password and tries to decrypt the file using this password
     * @param std::filesystem::path representing a path to a file with passwords
     * @return std::pair<std::string, std::vector<std::string>> containing a password and a vector of passwords
     */
    static std::pair<std::string, std::vector<std::string>> get_password_and_try_decrypt(const fs::path& path_to_file_with_passwords);
};


#endif //PASSWORD_MANAGER_MENU_HPP
