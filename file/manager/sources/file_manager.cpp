//
// Created by Cezary Petryka on 31/05/2023.
//

#include "../file_manager.hpp"

bool FileManager::check_if_file_exists(const fs::path& path) {
    return is_regular_file(fs::path(path));
}

bool FileManager::check_if_directory_exists(const fs::path &path) {
    return fs::is_directory(fs::path(path));
}

bool FileManager::check_if_directory_is_empty(const fs::path &path) {
    return fs::is_empty(path);
}

std::vector<fs::path> FileManager::get_all_files_from_directory(const fs::path& path) {
    std::vector<fs::path> result;

    for(const auto& entry : fs::directory_iterator(path)) {
        if(entry.is_regular_file()) {
            result.emplace_back(entry.path());
        }
    }

    return result;
}

fs::path FileManager::get_path_to_file_from_user() {
    auto str_path = std::string {};
    auto path = fs::path {};
    auto do_continue {true};

    while(do_continue) {
        std::cout << "Provide the path to a file: " << std::endl;
        std::getline(std::cin, str_path);

        path = fs::path {str_path};

        if(FileManager::check_if_file_exists(path)) {
            system("cls");
            return path;
        }
        else {
            std::cout << "File doesn't exist!" << std::endl;
            do_continue = Utilities::get_yes_or_no_from_user("Do you want to try again?");
        }
    }

    system("cls");
    return fs::path {""};
}

fs::path FileManager::select_file_from_directory_by_user(const fs::path& path_to_directory) {
    std::cout << "Choose one of the following files: " << std::endl;
    auto files = FileManager::get_all_files_from_directory(path_to_directory);
    for (int i = 0; i < files.size(); ++i) {
        std::cout << i + 1 << " -> " << files.at(i).string() << std::endl;
    }

    auto choice {0};

    while(true) {
        std::cout << "Chosen file number: ";
        std::cin >> choice; std::cin.get();

        if(choice < 1 || choice > files.size()) {
            std::cout << "There's no such option. Try again!" << std::endl;
            continue;
        }

        system("cls");
        return files.at(choice - 1);
    }
}
