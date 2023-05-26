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

std::vector<std::string> Menu::get_password_and_decrypt(const fs::path& path_to_file_with_passwords) {
    auto file_content = FileReader::read(path_to_file_with_passwords.string());

    auto do_continue {true};
    auto password = std::string {};
    auto decrypted_content = std::vector<std::string> {};
    auto attempts {0};

    while(do_continue) {
        // If user exceeds 3 attempts, then exit the program
        if(attempts++ == 3) {
            std::cout << "You've exceeded the number of attempts!" << std::endl;
            std::cout << "Exiting..." << std::endl;
            break;
        }

        // Get password from user
        std::cout << "Enter your password: ";
        std::getline(std::cin, password);

        // Decrypt file content
        decrypted_content = Encryptor::decrypt_all(file_content, password);

        // Validate decrypted content
        auto validator = PasswordValidator{};

        auto res = std::ranges::all_of(decrypted_content, [&validator](const auto& line) {
            return validator.validate(line) || line.empty();
        });

        // Final actions
        if(res) {
            do_continue = {false};
        }
        else {
            std::cout << "Wrong password! Try again!" << std::endl;
        }
    }

    return decrypted_content;
}
