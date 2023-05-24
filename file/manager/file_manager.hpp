//
// Created by Cezary Petryka on 23/05/2023.
//

#ifndef PASSWORD_MANAGER_FILE_MANAGER_HPP
#define PASSWORD_MANAGER_FILE_MANAGER_HPP

#include "../../libs/libs.hpp"

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
    static bool check_if_file_exists(const fs::path& path) {
        return is_regular_file(fs::path(path));
    }

    /**
     * @brief Gets all files from directory
     * @param std::filesystem::path representing a path to a directory
     * @return std::vector<std::filesystem::path> containing all files from a specified directory
     */
    static std::vector<fs::path> get_all_files_from_directory(const fs::path& path) {
        std::vector<fs::path> result;

        for(const auto& entry : fs::directory_iterator(path)) {
            if(entry.is_regular_file()) {
                result.emplace_back(entry.path());
            }
        }

        return result;
    }
};

#endif //PASSWORD_MANAGER_FILE_MANAGER_HPP
