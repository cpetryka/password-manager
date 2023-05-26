//
// Created by Cezary Petryka on 26/05/2023.
//

#include "../menu.hpp"

fs::path Menu::get_path_to_file_with_passwords_from_user(const fs::path& path_to_files_with_saved_passwords) {
    auto path = fs::path {};
    auto do_continue {true};

    while(do_continue) {
        std::cout << "=================================" << std::endl;
        std::cout << "1 -> use one of the saved files" << std::endl;
        std::cout << "2 -> provide your own path" << std::endl;
        std::cout << "9 -> exit" << std::endl;

        // Get user's choice
        std::cout << "Your choice: ";
        auto choice {0};
        std::cin >> choice; std::cin.get();

        // Perform action based on user's choice
        switch(choice) {
            case 1:
                {
                    std::cout << "Choose one of the following files: " << std::endl;
                    auto files = FileManager::get_all_files_from_directory(path_to_files_with_saved_passwords);
                    for (int i = 0; i < files.size(); ++i) {
                        std::cout << i + 1 << " -> " << files.at(i).string() << std::endl;
                    }

                    std::cout << "Chosen file number: ";
                    std::cin >> choice; std::cin.get();

                    if(choice < 1 || choice > files.size()) {
                        std::cout << "There's no such option!" << std::endl;
                        std::cout << "Try again!" << std::endl;
                        break;
                    }

                    path = files.at(choice - 1);
                    do_continue = {false};
                }
                break;
            case 2:
                {
                    std::cout << "Provide your own path: ";
                    auto str_path = std::string {};
                    std::getline(std::cin, str_path);

                    path = fs::path {str_path};

                    if (FileManager::check_if_file_exists(path))
                        do_continue = {false};
                    else {
                        std::cout << "File doesn't exist!" << std::endl;
                        std::cout << "Try again!" << std::endl;
                    }
                }
                break;
            case 9:
                fs::path {""};
                do_continue = {false};
                break;
            default:
                std::cout << "There's no such option!" << std::endl;
                std::cout << "Try again!" << std::endl;
        }

        return path;
    }
}
