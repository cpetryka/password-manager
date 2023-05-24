//
// Created by Cezary Petryka on 23/05/2023.
//

#ifndef PASSWORD_MANAGER_FILE_MANAGER_HPP
#define PASSWORD_MANAGER_FILE_MANAGER_HPP

#include "../../libs/libs.hpp"

struct FileManager {
    static bool check_if_file_exists(const fs::path& path) {
        return is_regular_file(fs::path(path));
    }

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
