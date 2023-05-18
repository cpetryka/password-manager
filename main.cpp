#include "model/password.hpp"
#include "file/writer/file_writer.hpp"
#include "encription/encryptor.hpp"
#include "file/reader/file_reader.hpp"
#include "validator/password_validator.hpp"

int main() {
    /*// Model class test
    auto p = Password("Google password", "ala1248", "mail", "www.google.com", std::nullopt);
    std::cout << p << std::endl;

    // File writer test
    auto data = std::vector<std::string> {
        "ala", "ma", "kota"
    };

    FileWriter::save("test.txt", data);

    // File reader test
    auto read_data = FileReader::read("test.txt");
    std::ranges::for_each(read_data, [](const auto& line) {
        std::cout << line << std::endl;
    });

    // Encryptor test
    auto encryptor = Encryptor("password");

    auto encrypted = encryptor.encrypt("Ala ma kota\nDzis jest 14 maja 2023 roku");
    std::cout << encrypted << std::endl;

    auto decrypted = encryptor.decrypt(encrypted);
    std::cout << decrypted << std::endl;*/

    /*auto passwords_strings = FileReader::read("passwords.txt");

    for (const auto& password : passwords_strings) {
        std::cout << password << std::endl;
        std::cout << "==> " << PasswordValidator::validate(password) << std::endl;
    }*/

    // Hello + wybieranie pliku (z folderu lub z dysku)
    // Podawanie hasla w celu odszyfrownaia -> timestamp

    // Menu
    // 1. Wyszukja hasla
    // 2. Posortuj hasla
    // 3. Dodaj haslo
    // 4. Edytuj haslo
    // 5. Usun haslo
    // 6. Dodaj kategorie
    // 7. Usun kategorie
    // 8. Wyjscie z programu + zapisanie zmian

    return 0;
}