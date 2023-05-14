#include "model/password.hpp"
#include "file/writer/file_writer.hpp"

int main() {
    auto p = Password("Google password", "ala1248", "mail", "www.google.com", std::nullopt);
    std::cout << p << std::endl;

    auto data = std::vector<std::string> {
        "ala", "ma", "kota"
    };

    FileWriter::save("test.txt", data);

    return 0;
}