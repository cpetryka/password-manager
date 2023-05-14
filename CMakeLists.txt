cmake_minimum_required(VERSION 3.25)
project(password_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(password_manager main.cpp libs/libs.hpp model/sources/password.cpp model/password.hpp file/writer/file_writer.hpp file/writer/exception/file_writer_exception.hpp)
