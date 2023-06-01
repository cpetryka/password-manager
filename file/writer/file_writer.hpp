//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_FILE_WRITER_HPP
#define PASSWORD_MANAGER_FILE_WRITER_HPP

#include "../../libs/libs.hpp"
#include "exception/file_writer_exception.hpp"

/**
 * @brief Class for writing data to file
 */
struct FileWriter {
    /**
     * @brief Saves data to file
     * @tparam T representing the type of data to save
     * @param std::filesystem::path representing a path to a file
     * @param std::vector<T> representing data to save
     */
    template<typename T>
    static void save(const fs::path& path, const std::vector<T>& data) {
        std::ofstream out { path };

        if(!out.is_open()) {
            throw FileWriterException("FileWriter::save: file " + path.string() + " cannot be opened");
        }

        std::ranges::for_each(data, [&out](const auto& password) {
            out << password << std::endl;
        });
    }
};

#endif //PASSWORD_MANAGER_FILE_WRITER_HPP
