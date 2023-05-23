#include "model/password.hpp"
#include "file/writer/file_writer.hpp"
#include "encription/encryptor.hpp"
#include "file/reader/file_reader.hpp"
#include "validator/password_validator.hpp"
#include "file/manager/file_manager.hpp"

int main() {
    const auto SAVED_PASSWORDS_PATH = fs::path {"C:\\Users\\Cezary Petryka\\Desktop\\password-manager\\cmake-build-debug\\saved_passwords"};

    std::cout << "Welcome to Password Manager!" << std::endl;
    std::cout << "Decide whether you want to use one of the saved files with passwords or if you want to provide your own path." << std::endl;

    auto path = fs::path {};
    auto choice {0};
    auto do_continue {true};

    while(do_continue) {
        std::cout << "=================================" << std::endl;
        std::cout << "1 -> use one of the saved files" << std::endl;
        std::cout << "2 -> provide your own path" << std::endl;
        std::cout << "9 -> exit" << std::endl;

        std::cout << "Your choice: ";
        std::cin >> choice; std::cin.get();

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

    std::cout << "Chosen path: " << path << std::endl;

    return 0;
}