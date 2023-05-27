//
// Created by Cezary Petryka on 16/05/2023.
//

#include "../password_manager.hpp"

std::vector<std::pair<password_field, std::string>> PasswordManager::get_criteria_from_user() noexcept {
    std::vector<std::pair<password_field, std::string>> criteria;

    while(true) {
        std::cout << "========== CRITERIA CHOOSER ==========" << std::endl;
        auto choice = PasswordField::choose_field_menu();

        std::cout << "Provide additional information for the chosen field: ";
        auto additional_info = std::string {};
        std::getline(std::cin, additional_info);

        criteria.emplace_back(choice, additional_info);

        std::cout << "Do you want to add another criteria? (y/n): ";
        auto answer = std::string {};
        std::getline(std::cin, answer);

        if(answer == "n") {
            break;
        }
    }


    return criteria;
}


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

std::vector<std::unique_ptr<Password>> PasswordManager::get_passwords() noexcept {
    auto criteria = get_criteria_from_user();

    auto result = std::vector<std::unique_ptr<Password>> {};

    for(const auto& password : passwords) {
        auto is_password_meeting_criteria = true;

        for(const auto& [field, additional_info] : criteria) {
            if(!password->check_match(field, additional_info)) {
                is_password_meeting_criteria = false;
                break;
            }
        }

        if(is_password_meeting_criteria) {
            result.emplace_back(std::make_unique<Password>(*password));
        }
    }

    return result;
}

void PasswordManager::menu() noexcept {
    auto choice {0};

    while(true) {
        std::cout << "========== MAIN MENU ==========" << std::endl;
        std::cout << "1. Show all passwords" << std::endl;
        std::cout << "2. Show passwords that match the given criteria" << std::endl;
        std::cout << "9. Exit" << std::endl;

        std::cout << "Your choice: ";
        std::cin >> choice; std::cin.get();

        switch(choice) {
            case 1:
                std::cout << "========== PASSWORDS ==========" << std::endl;
                std::ranges::for_each(passwords, [](const auto& password) {
                    std::cout << *password << std::endl;
                });

                break;
            case 2:
                {
                    auto criteria_passwords = get_passwords();

                    std::cout << "========== PASSWORDS ==========" << std::endl;
                    std::ranges::for_each(criteria_passwords, [](const auto& password) {
                        std::cout << *password << std::endl;
                    });
                }
                break;
            case 9:
                return;
            default:
                std::cout << "There is no such option! Try again!" << std::endl;
        }
    }
}

std::ostream &operator<<(std::ostream &out, const PasswordManager &pm) noexcept {
    std::ranges::for_each(pm.passwords, [&out](const auto& password) {
        out << *password << '\n';
    });

    return out;
}