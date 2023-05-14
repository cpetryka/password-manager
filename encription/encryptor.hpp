//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_ENCRYPTOR_HPP
#define PASSWORD_MANAGER_ENCRYPTOR_HPP

#include "../libs/libs.hpp"

class Encryptor {
    std::string seed;
public:
    explicit Encryptor(const std::string& encryption_seed) : seed{encryption_seed} {}

    std::string encrypt(const std::string& expression) const {
        std::string encrypted_expression;
        auto first_last_letters_difference = std::abs(seed.front() - seed.back());

        for(auto i = 0; i < expression.size(); ++i) {
            /*if(i % 2 == 0) {
                encrypted_expression += static_cast<char>(expression[i] + seed[i % seed.size()]);
            } else {
                encrypted_expression += static_cast<char>(expression[i] - seed[i % seed.size()]);
            }*/

            if(i % 2 == 0) {
                encrypted_expression += static_cast<char>(expression[i] + first_last_letters_difference);
            } else {
                encrypted_expression += static_cast<char>(expression[i] - first_last_letters_difference);
            }
        }

        return encrypted_expression;
    }

    std::string decrypt(const std::string& expression) const {
        std::string decrypted_expression;
        auto first_last_letters_difference = std::abs(seed.front() - seed.back());

        for(auto i = 0; i < expression.size(); ++i) {
            /*if(i % 2 == 0) {
                decrypted_expression += static_cast<char>(expression[i] - seed[i % seed.size()]);
            } else {
                decrypted_expression += static_cast<char>(expression[i] + seed[i % seed.size()]);
            }*/

            if(i % 2 == 0) {
                decrypted_expression += static_cast<char>(expression[i] - first_last_letters_difference);
            } else {
                decrypted_expression += static_cast<char>(expression[i] + first_last_letters_difference);
            }
        }

        return decrypted_expression;
    }
};

#endif //PASSWORD_MANAGER_ENCRYPTOR_HPP
