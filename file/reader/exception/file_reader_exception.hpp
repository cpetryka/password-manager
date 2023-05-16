//
// Created by Cezary Petryka on 16/05/2023.
//

#ifndef PASSWORD_MANAGER_FILE_READER_EXCEPTION_HPP
#define PASSWORD_MANAGER_FILE_READER_EXCEPTION_HPP

#include "../../../libs/libs.hpp"

class FileReaderException : public std::exception {
    std::string message;
public:
    explicit FileReaderException(const std::string& message) : message{message} {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //PASSWORD_MANAGER_FILE_READER_EXCEPTION_HPP
