#include "model/password.hpp"

int main() {
    auto p = Password("Google password", "ala1248", "mail", "www.google.com", std::nullopt);
    std::cout << p << std::endl;

    return 0;
}