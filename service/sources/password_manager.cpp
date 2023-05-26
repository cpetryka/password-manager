//
// Created by Cezary Petryka on 16/05/2023.
//

#include "../password_manager.hpp"

PasswordManager::PasswordManager(const std::vector<std::unique_ptr<Password>> &passwords) noexcept {
    std::ranges::for_each(passwords, [this](const auto& password) {
        this->passwords.emplace_back(std::make_unique<Password>(*password));
    });
}

PasswordManager::PasswordManager(const PasswordManager &pm) noexcept {
    std::ranges::for_each(pm.passwords, [this](const auto& password) {
        this->passwords.emplace_back(std::make_unique<Password>(*password));
    });
}

PasswordManager::PasswordManager(PasswordManager &&pm) noexcept : passwords {std::move(pm.passwords)} {}

PasswordManager &PasswordManager::operator=(const PasswordManager &pm) {
    if(this == &pm) {
        return *this;
    }

    std::ranges::for_each(pm.passwords, [this](const auto& password) {
        this->passwords.emplace_back(std::make_unique<Password>(*password));
    });

    return *this;
}

PasswordManager &PasswordManager::operator=(PasswordManager &&pm) noexcept {
    if(this == &pm) {
        return *this;
    }

    passwords = std::move(pm.passwords);

    return *this;
}
