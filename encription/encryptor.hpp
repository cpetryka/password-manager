//
// Created by Cezary Petryka on 14/05/2023.
//

#ifndef PASSWORD_MANAGER_ENCRYPTOR_HPP
#define PASSWORD_MANAGER_ENCRYPTOR_HPP

#include "../libs/libs.hpp"

/**
 * @brief Class used to encrypt and decrypt passwords
 * @details All the methods are static, so there is no need to create an object of this class.
 */
struct Encryptor {
    explicit Encryptor() = default;

    /**
     * @brief Encrypts expression passed as an argument
     * @param std::string representing an expression to encrypt
     * @param std::string representing password which will be used to encrypt the expression
     * @return std::string representing encrypted expression
     */
    static std::string encrypt(const std::string& expression, const std::string& password);

    /**
     * @brief Decrypts expression passed as an argument
     * @param std::string representing an expression to decrypt
     * @param std::string representing password which will be used to decrypt the expression
     * @return std::string representing decrypted expression
     */
    static std::string decrypt(const std::string& expression, const std::string& password);

    /**
     * @brief Decrypts all expressions passed as an argument
     * @param std::vector<std::string> representing expressions to decrypt
     * @param std::string representing password which will be used to decrypt the expressions
     * @return std::vector<std::string> representing decrypted expressions
     */
    static std::vector<std::string> decrypt_all(const std::vector<std::string>& expressions, const std::string& password);
};

#endif //PASSWORD_MANAGER_ENCRYPTOR_HPP
