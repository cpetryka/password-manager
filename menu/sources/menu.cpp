//
// Created by Cezary Petryka on 26/05/2023.
//

#include "../menu.hpp"

fs::path Menu::get_path_to_file_with_passwords_from_user(const fs::path& path_to_files_with_saved_passwords) {
    auto path = fs::path {};
    auto do_continue {true};
    auto choice {0};

    while(do_continue) {
        // Print menu
        std::cout << "Decide whether you want to use one of the saved files with passwords or if you want to provide your own path." << std::endl;
        std::cout << "============ MAIN MENU ============" << std::endl;
        std::cout << "1 -> use one of the saved files" << std::endl;
        std::cout << "2 -> provide your own path" << std::endl;
        std::cout << "9 -> exit" << std::endl;

        // Get user's choice
        std::cout << "Your choice: ";
        std::cin >> choice; std::cin.get();

        // Perform action based on user's choice
        system("cls");
        switch(choice) {
            case 1:
                path = FileManager::select_file_from_directory_by_user(path_to_files_with_saved_passwords);
                do_continue = {false};
                break;
            case 2:
                path = FileManager::get_path_to_file_from_user();
                do_continue = {false};
                break;
            case 9:
                std::cout << "Exiting..." << std::endl;
                exit(0);
            default:
                system("cls");
                std::cout << "There's no such option. Try again!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                system("cls");
        }
    }

    return path;
}

std::pair<std::string, std::vector<std::string>> Menu::get_password_and_try_decrypt(const fs::path& path_to_file_with_passwords) {
    // Read file content
    auto encrypted_file_content = FileReader::read(path_to_file_with_passwords);

    auto attempts {0};
    auto password = std::string {};
    auto decrypted_content = std::vector<std::string> {};

    while(true) {
        // Get password from user
        std::cout << "Enter your password: ";
        std::getline(std::cin, password);

        // Decrypt file content
        decrypted_content = Encryptor::decrypt_all(encrypted_file_content, password);

        // Validate decrypted content
        auto decryption_success_test = std::ranges::all_of(decrypted_content, [](const auto& line) {
            return PasswordValidator::validate(line) || line.empty();
        });

        // Final actions
        if(decryption_success_test) {
            return std::make_pair(password, decrypted_content);
        }
        else if(attempts < 2) {
            std::cout << "Wrong password! Try again!" << std::endl;
        }
        else {
            std::cout << "You've exceeded the number of attempts!" << std::endl;
            break;
        }

        attempts++;
    }

    // If user has exceeded the number of attempts, return empty vector
    password.clear();
    decrypted_content.clear();
    return std::make_pair(password, decrypted_content);
}
