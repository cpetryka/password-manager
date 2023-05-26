cmake_minimum_required(VERSION 3.25)
project(password_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(password_manager main.cpp libs/libs.hpp model/sources/password.cpp model/password.hpp file/writer/file_writer.hpp file/writer/exception/file_writer_exception.hpp encription/sources/encryptor.cpp encription/encryptor.hpp file/reader/file_reader.hpp file/reader/exception/file_reader_exception.hpp service/sources/password_manager.cpp service/password_manager.hpp validator/password_validator.hpp validator/validator.hpp file/manager/file_manager.hpp parser/parser.hpp parser/password_parser.hpp utilities/sources/utilities.cpp utilities/utilities.hpp menu/menu.hpp menu/sources/menu.cpp)
