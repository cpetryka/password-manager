//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_FILE_READER_HPP
#define PASSWORD_MANAGER_FILE_READER_HPP

#include "../../libs/libs.hpp"
#include "exception/file_reader_exception.hpp"

/**
 * @brief Class for reading data from file
 */
struct FileReader {
    /**
     * @brief Reads data from file
     * @param std::string representing a path to a file
     * @return std::vector<std::string> containing data from file
     */
    static std::vector<std::string> read(const std::string& path) {
        std::ifstream in { path };

        if(!in.is_open()) {
            throw FileReaderException("FileReader::read: file " + path + " cannot be opened");
        }

        std::vector<std::string> result;
        std::string line;

        while(!in.eof()) {
            std::getline(in, line);

            if(line.empty()) {
                continue;
            }

            result.emplace_back(line);
        }

        return result;
    }
};


#endif //PASSWORD_MANAGER_FILE_READER_HPP
