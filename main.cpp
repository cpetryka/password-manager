#include "model/password.hpp"
#include "file/writer/file_writer.hpp"
#include "encription/encryptor.hpp"
#include "file/reader/file_reader.hpp"
#include "validator/password_validator.hpp"
#include "file/manager/file_manager.hpp"
#include "parser/password_parser.hpp"

int main() {
    const auto SAVED_PASSWORDS_PATH = fs::path {"C:\\Users\\Cezary Petryka\\Desktop\\password-manager\\cmake-build-debug\\saved_passwords"};

    std::cout << "Welcome to Password Manager!" << std::endl;
    std::cout << "Decide whether you want to use one of the saved files with passwords or if you want to provide your own path." << std::endl;

    // User's choice whether to use one of the saved files or to provide his own path
    auto path = fs::path {};
    auto choice {0};
    auto do_continue {true};

    while(do_continue) {
        std::cout << "=================================" << std::endl;
        std::cout << "1 -> use one of the saved files" << std::endl;
        std::cout << "2 -> provide your own path" << std::endl;
        std::cout << "9 -> exit" << std::endl;

        // Get user's choice
        std::cout << "Your choice: ";
        std::cin >> choice; std::cin.get();

        // Perform action based on user's choice
        switch(choice) {
            case 1:
                {
                    std::cout << "Choose one of the following files: " << std::endl;
                    auto files = FileManager::get_all_files_from_directory(SAVED_PASSWORDS_PATH);
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

                    if(FileManager::check_if_file_exists(path)) {
                        do_continue = {false};
                    } else {
                        std::cout << "File doesn't exist!" << std::endl;
                        std::cout << "Try again!" << std::endl;
                    }
                }
                break;
            case 9:
                return 0;
            default:
                std::cout << "There's no such option!" << std::endl;
                std::cout << "Try again!" << std::endl;
        }
    }

    // The result of the code above is the path to the file with passwords

    std::cout << "Chosen path: " << path << std::endl;

    // Decryption of the file
    auto file_content = FileReader::read(path.string());

    do_continue = {true};
    auto password = std::string {};
    auto decrypted_content = std::vector<std::string> {};
    auto attempts = 0;

    while(do_continue) {
        // If user exceeds 3 attempts, then exit the program
        if(attempts++ == 3) {
            std::cout << "You've exceeded the number of attempts!" << std::endl;
            std::cout << "Exiting..." << std::endl;
            return 0;
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

    // The result of the code above is the decrypted content of the file

    std::vector<std::unique_ptr<Password>> passwords;
    auto parser = PasswordParser{};

    std::ranges::transform(decrypted_content, std::back_inserter(passwords), [&parser](const auto& line) {
        return std::make_unique<Password>(*parser.parse(line));
    });

    std::ranges::for_each(passwords, [](const auto& password) {
        std::cout << *password << std::endl;
    });

    return 0;
}