//
// Created by Cezary Petryka on 28/05/2023.
//

#ifndef PASSWORD_MANAGER_PASSWORD_STRENGTH_HPP
#define PASSWORD_MANAGER_PASSWORD_STRENGTH_HPP

#include "../libs/libs.hpp"

/**
 * @brief Namespace containing all possible password strength
 */
namespace PasswordStrength {
    enum class Type {
        VERY_WEAK,
        WEAK,
        MEDIUM,
        STRONG,
        VERY_STRONG
    };

    static Type Types[] = {
            Type::VERY_WEAK,
            Type::WEAK,
            Type::MEDIUM,
            Type::STRONG,
            Type::VERY_STRONG
    };
    static int SIZE = 5;

    /**
     * @brief Function used to convert a "strength" to a string
     * @param type "Strength" to convert to a string
     * @return std::string containing the "strength" name
     */
    static std::string to_string(const Type& type) {
        std::vector<std::string> strings = {
                "very_weak",
                "weak",
                "medium",
                "strong",
                "very_strong"
        };
        return strings[static_cast<int>(type)];
    }
}

using password_strength = PasswordStrength::Type;

#endif //PASSWORD_MANAGER_PASSWORD_STRENGTH_HPP
