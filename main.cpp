#include "model/password.hpp"
#include "service/password_manager.hpp"

int main() {
    srand(time(nullptr));

    auto password_manager = PasswordManager{};
    password_manager.menu();

    return 0;
}