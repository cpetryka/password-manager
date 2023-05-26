#include "model/password.hpp"
#include "file/writer/file_writer.hpp"
#include "encription/encryptor.hpp"
#include "file/reader/file_reader.hpp"
#include "validator/password_validator.hpp"
#include "file/manager/file_manager.hpp"
#include "parser/password_parser.hpp"
#include "menu/menu.hpp"

int main() {
    const auto SAVED_PASSWORDS_PATH = fs::path {"C:\\Users\\Cezary Petryka\\Desktop\\password-manager\\cmake-build-debug\\saved_passwords"};

    std::cout << "Welcome to Password Manager!" << std::endl;
    std::cout << "Decide whether you want to use one of the saved files with passwords or if you want to provide your own path." << std::endl;

    // User's choice whether to use one of the saved files or to provide his own path
    auto path = Menu::get_path_to_file_with_passwords_from_user(SAVED_PASSWORDS_PATH);

    if(path.empty()) {
        std::cout << "Exiting..." << std::endl;
        return 0;
    }

    // ...

    auto do_continue {true};

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
    
    // The result of the code above is the vector of Password objects

    return 0;
}