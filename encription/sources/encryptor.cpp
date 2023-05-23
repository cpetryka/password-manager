//
// Created by Cezary Petryka on 14/05/2023.
//

#include "../encryptor.hpp"

std::string Encryptor::encrypt(const std::string &expression, const std::string& password)  {
    std::string encrypted_expression;
    auto first_last_letters_difference = std::abs(password.front() - password.back());

    for(auto i = 0; i < expression.size(); ++i) {
        if(i % 2 == 0) {
            encrypted_expression += static_cast<char>(expression[i] + first_last_letters_difference);
        } else {
            encrypted_expression += static_cast<char>(expression[i] - first_last_letters_difference);
        }
    }

    return encrypted_expression;
}

std::string Encryptor::decrypt(const std::string &expression, const std::string& password) {
    std::string decrypted_expression;
    auto first_last_letters_difference = std::abs(password.front() - password.back());

    for(auto i = 0; i < expression.size(); ++i) {
        if(i % 2 == 0) {
            decrypted_expression += static_cast<char>(expression[i] - first_last_letters_difference);
        } else {
            decrypted_expression += static_cast<char>(expression[i] + first_last_letters_difference);
        }
    }

    return decrypted_expression;
}

std::vector<std::string>
Encryptor::decrypt_all(const std::vector<std::string> &expressions, const std::string &password) {
    std::vector<std::string> decrypted_expressions;

    std::ranges::for_each(expressions, [&decrypted_expressions, &password](const auto& expression) {
        decrypted_expressions.push_back(decrypt(expression, password));
    });

    return decrypted_expressions;
}
