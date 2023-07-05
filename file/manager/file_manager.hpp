//
// Created by Cezary Petryka on 23/05/2023.
//

#ifndef PASSWORD_MANAGER_FILE_MANAGER_HPP
#define PASSWORD_MANAGER_FILE_MANAGER_HPP

#include "../../libs/libs.hpp"
#include "../../utilities/utilities.hpp"

/**
 * @brief Class with some useful methods to manage files
 * @details All the methods are static, so there is no need to create an object of this class.
 */
struct FileManager {

    /**
     * @brief Checks if file exists
     * @param std::string representing a path to a file
     * @return true if file exists, false otherwise
     */
    static bool check_if_file_exists(const fs::path& path);

    /**
     * @brief Checks if directory exists
     * @param std::string representing a path to a directory
     * @return true if directory exists, false otherwise
     */
    static bool check_if_directory_exists(const fs::path& path);

    /**
     * @brief Checks if directory is empty
     * @param std::string representing a path to a directory
     * @return true if directory is empty, false otherwise
     */
    static bool check_if_directory_is_empty(const fs::path& path);

    /**
     * @brief Gets all files from directory
     * @param std::filesystem::path representing a path to a directory
     * @return std::vector<std::filesystem::path> containing all files from a specified directory
     */
    static std::vector<fs::path> get_all_files_from_directory(const fs::path& path);

    /**
     * @brief Gets a path to a file from user
     * @return std::filesystem::path representing a path to a file
     * @details The method checks if the file exists. If not, the user is asked if he/she wants to try again.
     */
    static fs::path get_path_to_file_from_user();

    /**
     * @brief Lets user choose a file from a specified directory
     * @param path_to_directory std::filesystem::path representing a path to a directory
     * @return std::filesystem::path representing a path to a file
     */
    static fs::path select_file_from_directory_by_user(const fs::path& path_to_directory);
};

#endif //PASSWORD_MANAGER_FILE_MANAGER_HPP
