#include "model/password.hpp"
#include "file/writer/file_writer.hpp"
#include "encription/encryptor.hpp"

int main() {
    auto p = Password("Google password", "ala1248", "mail", "www.google.com", std::nullopt);
    std::cout << p << std::endl;

    auto data = std::vector<std::string> {
        "ala", "ma", "kota"
    };

    FileWriter::save("test.txt", data);

    auto encryptor = Encryptor("password");

    auto encrypted = encryptor.encrypt("Ala ma kota\nDzis jest 14 maja 2023 roku");
    std::cout << encrypted << std::endl;

    auto decrypted = encryptor.decrypt(encrypted);
    std::cout << decrypted << std::endl;

    return 0;
}