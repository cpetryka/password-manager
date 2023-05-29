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

void PasswordManager::refresh_categories_set() noexcept {
    // clear the set because there might be some old categories that are no longer in use
    categories.clear();

    for (const auto& password_ptr : passwords) {
        categories.emplace(Utilities::to_lowercase(password_ptr->get_category()));
    }
}

bool PasswordManager::do_category_exists(const std::string &category) const noexcept {
    return categories.contains(category);
}

std::string PasswordManager::get_categories_string() const noexcept {
    auto result = std::string {"["};

    for(const auto& category : categories) {
        result += category + ", ";
    }

    // remove the last ", "
    result = result.substr(0, result.size() - 2);

    return result + "]";
}

bool PasswordManager::check_if_password_has_already_been_used(const std::string& password) const noexcept {
    return std::ranges::any_of(passwords, [&password](const auto& password_ptr) {
        return password_ptr->is_password_the_same(password);
    });
}

std::vector<std::string> PasswordManager::generate_decrypted_output_vector() const noexcept {
    auto result = std::vector<std::string> {};

    std::ranges::for_each(passwords, [&](const auto& password_ptr) {
        result.emplace_back(Encryptor::encrypt(password_ptr->get_raw_string(";"), master_password));
    });

    return result;
}

PasswordManager::PasswordManager(const fs::path& path_to_file_with_passwords,
                                 const std::string& master_password,
                                 const std::vector<std::unique_ptr<Password>> &passwords) noexcept
                                 : path_to_file_with_passwords{path_to_file_with_passwords},
                                 master_password{master_password} {
    std::ranges::for_each(passwords, [this](const auto& password) {
        this->passwords.emplace_back(std::make_unique<Password>(*password));
    });

    refresh_categories_set();
}

PasswordManager::PasswordManager(const PasswordManager &pm) noexcept
    : path_to_file_with_passwords{pm.path_to_file_with_passwords}, master_password{pm.master_password} {
    std::ranges::for_each(pm.passwords, [this](const auto& password) {
        this->passwords.emplace_back(std::make_unique<Password>(*password));
    });

    refresh_categories_set();
}

PasswordManager::PasswordManager(PasswordManager &&pm) noexcept : path_to_file_with_passwords{std::move(pm.path_to_file_with_passwords)},
    master_password{std::move(pm.master_password)}, passwords {std::move(pm.passwords)} {
    refresh_categories_set();
}

PasswordManager &PasswordManager::operator=(const PasswordManager &pm) {
    if(this == &pm) {
        return *this;
    }

    path_to_file_with_passwords = pm.path_to_file_with_passwords;
    master_password = pm.master_password;

    std::ranges::for_each(pm.passwords, [this](const auto& password) {
        this->passwords.emplace_back(std::make_unique<Password>(*password));
    });

    refresh_categories_set();

    return *this;
}

PasswordManager &PasswordManager::operator=(PasswordManager &&pm) noexcept {
    if(this == &pm) {
        return *this;
    }

    path_to_file_with_passwords = std::move(pm.path_to_file_with_passwords);
    master_password = std::move(pm.master_password);
    passwords = std::move(pm.passwords);
    refresh_categories_set();

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

void PasswordManager::add_password_menu() noexcept {
    std::cout << "========== ADDING NEW PASSWORD ==========" << std::endl;

    std::cout << "Provide description: ";
    auto description = std::string {};
    std::getline(std::cin, description);

    std::cout << "Do you want to provide your own password (enter 1) or generate one (enter 2): ";
    auto user_choice {-1};
    std::cin >> user_choice; std::cin.get();

    auto password = std::string {};

    if(user_choice == 1) {
        auto do_continue = true;

        while(do_continue) {
            std::cout << "Provide password: ";
            std::getline(std::cin, password);

            std::cout << "The strength of the password is: " << PasswordStrength::to_string(Password::get_password_strength(password)) << std::endl;

            if(check_if_password_has_already_been_used(password)) {
                std::cout << "WARNING! This password has already been used!" << std::endl;
            }

            std::cout << "Do you want to provide another password? (y/n): ";
            auto answer = std::string {};
            std::getline(std::cin, answer);

            if(answer == "n") {
                do_continue = false;
            }
        }
    }
    else if(user_choice == 2) {
        std::cout << "How many characters should the password have? (min 8): ";
        auto number_of_characters {-1};
        std::cin >> number_of_characters; std::cin.get();

        if(number_of_characters < 8) {
            std::cout << "The number of characters cannot be less than 8! Exiting..." << std::endl;
            return;
        }

        std::cout << "Should the password contain upper and lower case letters? (y/n): ";
        auto answer = std::string {};
        std::getline(std::cin, answer);

        std::cout << "Should the password contain special characters? (y/n): ";
        auto answer2 = std::string {};
        std::getline(std::cin, answer2);

        password = Password::generate_password(number_of_characters, answer == "y", answer2 == "y");
    }
    else {
        std::cout << "There is no such option! Exiting..." << std::endl;
        return;
    }

    std::cout << "Available categories: " << get_categories_string() << std::endl;
    auto category = std::string {};
    do {
        std::cout << "Provide category: " << std::endl;
        std::getline(std::cin, category);
    } while(!do_category_exists(category));

    auto website_address = std::string {};
    do {
        std::cout << "Provide website address (enter '-' if you do not want to provide a login): ";
        std::getline(std::cin, website_address);
    } while(!PasswordValidator::is_website_address_valid(website_address));

    std::cout << "Provide login (enter '-' if you do not want to provide a login): ";
    auto login = std::string {};
    std::getline(std::cin, login);

    passwords.emplace_back(std::make_unique<Password>(description, password, category, website_address, login));
}

void PasswordManager::edit_password_menu() noexcept {
    std::cout << "========== PASSWORDS ==========" << std::endl;
    for (int i = 0; i < passwords.size(); ++i) {
        std::cout << (i + 1) << ". " << *passwords[i] << std::endl;
    }

    std::cout << "Which password do you want to edit? Enter number (0 to cancel): ";
    auto user_choice {-1};
    std::cin >> user_choice; std::cin.get();

    if(user_choice == 0) {
        return;
    }
    std::cout << "========== EDITING PASSWORD ==========" << std::endl;
    std::cout << "What do you want to edit?" << std::endl;
    auto field = PasswordField::choose_field_menu();

    auto new_value = std::string();
    auto i = 0;

    do {
        if(i == 3) {
            std::cout << "You have entered invalid value 3 times. Cancelling..." << std::endl;
            return;
        }

        if(i++ > 0) {
            std::cout << "Invalid value!" << std::endl;
        }

        std::cout << "Provide new value: ";
        std::getline(std::cin, new_value);
    } while (!passwords[user_choice - 1]->edit_password(field, new_value));
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

void PasswordManager::add_category_menu() noexcept {
    std::cout << "========== ADDING CATEGORY ==========" << std::endl;
    std::cout << "Provide category name: ";
    auto category_name = std::string();
    std::getline(std::cin, category_name);

    if(categories.contains(category_name)) {
        std::cout << "Category with this name already exists!" << std::endl;
        return;
    }

    categories.emplace(Utilities::to_lowercase(category_name));
    std::cout << "Category added successfully!" << std::endl;
}

void PasswordManager::remove_category_menu() noexcept {
    std::cout << "========== REMOVING CATEGORY ==========" << std::endl;
    std::cout << "Provide category name: ";
    auto category_name = std::string();
    std::getline(std::cin, category_name);

    if(!categories.contains(Utilities::to_lowercase(category_name))) {
        std::cout << "Category with this name does not exist!" << std::endl;
        return;
    }

    categories.erase(Utilities::to_lowercase(category_name));
    std::cout << "Category removed successfully!" << std::endl;

    // Remove all passwords that were in this category
    auto to_erase = std::ranges::remove_if(passwords, [&category_name](const auto& password) {
        return password->get_category() == category_name;
    });

    passwords.erase(to_erase.begin(), to_erase.end());
}

void PasswordManager::menu() noexcept {
    auto choice {0};

    while(true) {
        std::cout << "========== MAIN MENU ==========" << std::endl;
        std::cout << "1. Show all passwords" << std::endl;
        std::cout << "2. Show passwords that match the given criteria" << std::endl;
        std::cout << "4. Add password" << std::endl;
        std::cout << "5. Edit password" << std::endl;
        std::cout << "6. Remove passwords" << std::endl;
        std::cout << "7. Add category" << std::endl;
        std::cout << "8. Remove category" << std::endl;
        std::cout << "9. Save changes and exit" << std::endl;

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
            case 4:
                add_password_menu();
                break;
            case 5:
                edit_password_menu();
                break;
            case 6:
                remove_passwords_menu();
                break;
            case 7:
                add_category_menu();

                std::cout << "The categories are now: " << std::endl;
                std::ranges::for_each(categories, [](const auto& category) {
                    std::cout << category << std::endl;
                });
                break;
            case 8:
                remove_category_menu();
                break;
            case 9:
                FileWriter::save(
                        path_to_file_with_passwords.replace_filename(fs::path{"saved.txt"}).string(),
                        generate_decrypted_output_vector()
                );

                std::cout << "Changes saved successfully!" << std::endl;

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