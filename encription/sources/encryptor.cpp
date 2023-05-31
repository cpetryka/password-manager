//
// Created by Cezary Petryka on 14/05/2023.
//

#include "../encryptor.hpp"

std::string Encryptor::encrypt(const std::string &expression, const std::string& password)  {
    std::string encrypted_expression;
    auto i {0};

    std::ranges::for_each(expression, [&password, &encrypted_expression, &i](const auto& character) {
        auto seed = password.at(i % password.size()) % 11 + 10;
        encrypted_expression += static_cast<char>(character + seed);
        i++;
    });

    return encrypted_expression;
}

std::string Encryptor::decrypt(const std::string &expression, const std::string& password) {
    std::string decrypted_expression;
    auto i {0};

    std::ranges::for_each(expression, [&password, &decrypted_expression, &i](const auto& character) {
        auto seed = password.at(i % password.size()) % 11 + 10;
        decrypted_expression += static_cast<char>(character - seed);
        i++;
    });

    return decrypted_expression;
}

std::vector<std::string>
Encryptor::decrypt_all(const std::vector<std::string> &expressions, const std::string &password) {
    std::vector<std::string> decrypted_expressions;

    std::ranges::for_each(expressions, [&decrypted_expressions, &password](const auto& expression) {
        decrypted_expressions.emplace_back(decrypt(expression, password));
    });

    return decrypted_expressions;
}
