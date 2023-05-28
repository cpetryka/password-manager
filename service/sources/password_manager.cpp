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

void PasswordManager::remove_passwords_menu() {
    std::cout << "========== PASSWORDS ==========" << std::endl;
    for (int i = 0; i < passwords.size(); ++i) {
        std::cout << (i + 1) << ". " << *passwords[i] << std::endl;
    }

    std::cout << "Which passwords do you want to remove? Enter numbers separated by spaces (0 to cancel): ";
    auto user_choice = std::string();
    std::getline(std::cin, user_choice);

    if(user_choice == "0") {
        return;
    }

    std::cout << "Are you sure you want to remove selected passwords? (y/n): ";
    auto do_remove = std::string();
    std::getline(std::cin, do_remove);

    if(do_remove == "n") {
        return;
    }

    auto passwords_to_remove = Utilities::split_to_numbers(user_choice, " ");

    // We need to subtract 1 from each number, because the user sees the passwords from 1 to n, but the vector
    // is indexed from 0 to n - 1
    std::ranges::transform(passwords_to_remove, passwords_to_remove.begin(), [](const auto& number) {
        return number - 1;
    });

    remove_passwords_at_indexes(passwords_to_remove);

    std::cout << "Passwords removed successfully!" << std::endl;
}

void PasswordManager::remove_passwords_at_indexes(std::vector<int> &indexes) {
    std::ranges::sort(indexes);

    // We need to remove the passwords from the end, because if we remove them from the beginning, the indexes
    // of the remaining passwords will change
    for(auto it = indexes.rbegin(); it != indexes.rend(); ++it) {
        passwords.erase(passwords.begin() + *it);
    }
}

void PasswordManager::menu() noexcept {
    auto choice {0};

    while(true) {
        std::cout << "========== MAIN MENU ==========" << std::endl;
        std::cout << "1. Show all passwords" << std::endl;
        std::cout << "2. Show passwords that match the given criteria" << std::endl;
        std::cout << "6. Remove passwords" << std::endl;
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
            case 6:
                remove_passwords_menu();
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