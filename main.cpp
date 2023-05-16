#include "model/password.hpp"
#include "file/writer/file_writer.hpp"
#include "encription/encryptor.hpp"
#include "file/reader/file_reader.hpp"

int main() {
    // Model class test
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
    std::cout << decrypted << std::endl;

    return 0;
}