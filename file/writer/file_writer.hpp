//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_FILE_WRITER_HPP
#define PASSWORD_MANAGER_FILE_WRITER_HPP

#include "../../libs/libs.hpp"
#include "exception/file_writer_exception.hpp"

struct FileWriter {
    template<typename T>
    static void save(const std::string& path, const std::vector<T>& data) {
        std::ofstream out { path };

        if(!out.is_open()) {
            throw FileWriterException("FileWriter::save: file " + path + " cannot be opened");
        }

        std::ranges::for_each(data, [&out](const auto& password) {
            out << password << std::endl;
        });
    }
};

#endif //PASSWORD_MANAGER_FILE_WRITER_HPP
