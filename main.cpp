#include "model/password.hpp"
#include "file/writer/file_writer.hpp"
#include "encription/encryptor.hpp"
#include "file/reader/file_reader.hpp"
#include "validator/password_validator.hpp"
#include "file/manager/file_manager.hpp"
#include "parser/password_parser.hpp"
#include "menu/menu.hpp"
#include "service/password_manager.hpp"

int main() {
    const auto SAVED_PASSWORDS_PATH = fs::path {"C:\\Users\\Cezary Petryka\\Desktop\\password-manager\\cmake-build-debug\\saved_passwords"};
    const auto SEPARATOR = std::string {";"};

    std::cout << "Welcome to Password Manager!" << std::endl;
    std::cout << "Decide whether you want to use one of the saved files with passwords or if you want to provide your own path." << std::endl;

    // User's choice whether to use one of the saved files or to provide his own path
    auto path = Menu::get_path_to_file_with_passwords_from_user(SAVED_PASSWORDS_PATH);

    if(path.empty()) {
        std::cout << "Exiting..." << std::endl;
        return 0;
    }

    // Decryption of the file
    auto decrypted_content = Menu::get_password_and_decrypt(path);

    std::vector<std::unique_ptr<Password>> passwords;

    std::ranges::transform(decrypted_content, std::back_inserter(passwords), [&SEPARATOR](const auto& line) {
        return std::make_unique<Password>(PasswordParser::parse(line, SEPARATOR));
    });

    // Creating a PasswordManager object
    auto password_manager = PasswordManager {passwords};
    std::cout << password_manager << std::endl;

    return 0;
}