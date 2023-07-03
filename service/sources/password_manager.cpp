//
// Created by Cezary Petryka on 16/05/2023.
//

#include "../password_manager.hpp"

std::vector<password_field> PasswordManager::get_criteria_from_user() noexcept {
    std::vector<password_field> criteria;

    while(true) {
        system("cls");
        std::cout << "========== CRITERIA CHOOSER ==========" << std::endl;
        auto choice = PasswordField::choose_field_menu();

        criteria.push_back(choice);

        std::cout << "Do you want to add another criteria? (y/n): ";
        auto answer = std::string {};
        std::getline(std::cin, answer);

        if(answer == "n") {
            break;
        }
    }

    return criteria;
}

std::vector<std::pair<password_field, std::string>> PasswordManager::get_extended_criteria_from_user() noexcept {
    std::vector<std::pair<password_field, std::string>> criteria;

    while(true) {
        system("cls");
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
        categories.emplace(Utilities::to_lowercase(password_ptr->get_field(password_field::CATEGORY)));
    }
}

bool PasswordManager::do_category_exists(const std::string &category) const noexcept {
    return categories.contains(Utilities::to_lowercase(category));
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
        return password_ptr->compare_field_with(password_field::PASSWORD, password);
    });
}

std::vector<std::string> PasswordManager::generate_encrypted_output_vector() const noexcept {
    auto result = std::vector<std::string> {};

    std::ranges::for_each(passwords, [&](const auto& password_ptr) {
        result.emplace_back(Encryptor::encrypt(password_ptr->get_raw_string(SEPARATOR), master_password));
    });

    return result;
}

std::vector<std::string> PasswordManager::add_timestamp_to_vector(const std::vector<std::string>& vector) const noexcept {
    auto result = std::vector<std::string> {vector};
    auto timestamp_copy = last_decryption_timestamp;

    // If there is fewer than 8 elements in the vector, then we need to add empty strings to the vector
    while(result.size() < 8) {
        result.emplace_back("");
    }

    // Add the timestamp to the vector
    for(auto i = 1; i < 8; i += 2) {
        result.at(i) = timestamp_copy.substr(0, 4) + result.at(i);
        // result.emplace(result.begin() + i, timestamp_copy.substr(0, 4) + result.at(i));
        timestamp_copy = timestamp_copy.substr(4);
    }

    return result;
}

std::string PasswordManager::get_and_remove_timestamp_from_vector(std::vector<std::string>& vector) noexcept {
    auto timestamp_temp = std::string {};

    for(auto i = 1; i <= 7; i += 2) {
        timestamp_temp += vector.at(i).substr(0, 4);

        if(vector.at(i).size() > 4) {
            vector.at(i) = vector.at(i).substr(4);
        } else {
            vector.at(i) = "";
        }
    }

    return timestamp_temp;
}

fs::path PasswordManager::get_path_to_file_with_passwords_from_user() {
    auto path = fs::path {};
    auto do_continue {true};
    auto choice {0};

    while(do_continue) {
        // Print menu
        std::cout << "Decide whether you want to use one of the saved files with passwords or if you want to provide your own path." << std::endl;
        std::cout << "============ MAIN MENU ============" << std::endl;
        std::cout << "1 -> create new file" << std::endl;
        std::cout << "2 -> use one of the saved files" << std::endl;
        std::cout << "3 -> provide your own path" << std::endl;
        std::cout << "9 -> exit" << std::endl;

        // Get user's choice
        std::cout << "Your choice: ";
        std::cin >> choice; std::cin.get();

        // Perform action based on user's choice
        system("cls");
        switch(choice) {
            case 1:
                {
                    while(true) {
                        std::cout << "Enter the name of the file: ";
                        auto file_name = std::string {};
                        std::getline(std::cin, file_name);

                        path = SAVED_PASSWORDS_PATH / (file_name + ".txt");

                        if (FileManager::check_if_file_exists(path)) {
                            std::cout << "File with this name already exists. Try again!" << std::endl;
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            system("cls");
                            continue;
                        }

                        break;
                    }

                    do_continue = {false};
                    break;
                }
            case 2:
                path = FileManager::select_file_from_directory_by_user(SAVED_PASSWORDS_PATH);
                do_continue = {false};
                break;
            case 3:
                path = FileManager::get_path_to_file_from_user();
                do_continue = {false};
                break;
            case 9:
                std::cout << "Exiting..." << std::endl;
                exit(0);
            default:
                system("cls");
                std::cout << "There's no such option. Try again!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                system("cls");
        }
    }

    return path;
}

std::pair<std::string, std::vector<std::string>> PasswordManager::get_password_and_try_decrypt() {
    auto encrypted_file_content = std::vector<std::string> {8};

    if(FileManager::check_if_file_exists(path_to_file_with_passwords)) {
        // Read file content
        encrypted_file_content = FileReader::read(path_to_file_with_passwords);

        // Get timestamp from the file content, remove it from the vector and print it
        auto ldt = get_and_remove_timestamp_from_vector(encrypted_file_content);
        std::cout << "Last file decryption time: " << DateTimeUtilities::convert_raw_date_string_to_standard_format(ldt) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    auto attempts {0};
    auto password = std::string {};
    auto decrypted_content = std::vector<std::string> {};

    while(true) {
        // Get password from user
        std::cout << "Enter your password: ";
        std::getline(std::cin, password);

        // Decrypt file content
        decrypted_content = Encryptor::decrypt_all(encrypted_file_content, password);
        last_decryption_timestamp = DateTimeUtilities::get_current_date_and_time_as_raw_string();

        // Add timestamp to the vector and save it to the file
        auto vector_with_timestamp = add_timestamp_to_vector(encrypted_file_content);

        FileWriter::save(
                path_to_file_with_passwords,
                vector_with_timestamp
        );

        // Validate decrypted content
        auto decryption_success_test = std::ranges::all_of(decrypted_content, [](const auto& line) {
            return PasswordValidator::validate(line) || line.empty();
        });

        // Final actions
        if(decryption_success_test) {
            system("cls");
            return std::make_pair(password, decrypted_content);
        }
        else if(attempts < 2) {
            std::cout << "Wrong password! Try again!" << std::endl;
        }
        else {
            std::cout << "You've exceeded the number of attempts!" << std::endl;
            break;
        }

        attempts++;
    }

    // If user has exceeded the number of attempts, return empty vector
    password.clear();
    decrypted_content.clear();
    return std::make_pair(password, decrypted_content);
}


void PasswordManager::init() noexcept {
    auto separator = SEPARATOR;

    while(true) {
        system("cls");
        std::cout << "Welcome to Password Manager!" << std::endl;

        // User's choice whether to use one of the saved files or to provide his own path
        this->path_to_file_with_passwords = get_path_to_file_with_passwords_from_user();

        if(this->path_to_file_with_passwords.empty()) {
            system("cls");
            std::cout << "Something went wrong. Try again!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        // Decryption of the file
        auto pair = get_password_and_try_decrypt();
        last_decryption_timestamp = DateTimeUtilities::get_current_date_and_time_as_raw_string();

        if(pair.second.empty()) {
            system("cls");
            std::cout << "Something went wrong. Try again!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        // If the decryption was successful, then we can assign the master password and the passwords vector and break the loop
        this->master_password = pair.first;

        auto to_erase = std::ranges::remove_if(pair.second.begin(), pair.second.end(), [](const auto& line) {
            return line.empty();
        });
        pair.second.erase(to_erase.begin(), to_erase.end());

        if(!pair.second.empty()) {
            std::ranges::transform(pair.second, std::back_inserter(this->passwords), [&separator](const auto& line) {
                return std::make_unique<Password>(PasswordParser::parse(line, separator));
            });
        }

        break;
    }
}

PasswordManager::PasswordManager() noexcept {
    init();
    refresh_categories_set();
}

PasswordManager::PasswordManager(const PasswordManager &pm) noexcept
    : path_to_file_with_passwords{pm.path_to_file_with_passwords}, master_password{pm.master_password},
    last_decryption_timestamp{pm.last_decryption_timestamp} {
    std::ranges::for_each(pm.passwords, [this](const auto& password) {
        this->passwords.emplace_back(std::make_unique<Password>(*password));
    });

    refresh_categories_set();
}

PasswordManager::PasswordManager(PasswordManager &&pm) noexcept
    : path_to_file_with_passwords{std::move(pm.path_to_file_with_passwords)}, master_password{std::move(pm.master_password)},
    last_decryption_timestamp{std::move(pm.last_decryption_timestamp)}, passwords{std::move(pm.passwords)} {
    refresh_categories_set();
}

PasswordManager &PasswordManager::operator=(const PasswordManager &pm) {
    if(this == &pm) {
        return *this;
    }

    path_to_file_with_passwords = pm.path_to_file_with_passwords;
    master_password = pm.master_password;
    last_decryption_timestamp = pm.last_decryption_timestamp;

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
    last_decryption_timestamp = std::move(pm.last_decryption_timestamp);
    passwords = std::move(pm.passwords);
    refresh_categories_set();

    return *this;
}

std::vector<std::unique_ptr<Password>> PasswordManager::get_passwords() noexcept {
    auto criteria = get_extended_criteria_from_user();

    auto result = std::vector<std::unique_ptr<Password>> {};

    for(const auto& password : passwords) {
        auto is_password_meeting_criteria = true;

        for(const auto& [field, additional_info] : criteria) {
            if(!password->compare_field_with(field, additional_info)) {
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

void PasswordManager::sort_passwords(const std::vector<password_field> &criteria) noexcept {
    std::ranges::sort(passwords, [&criteria](const auto& lhs, const auto& rhs) {
        for(const auto& one_criteria : criteria) {
            const auto lhs_field_value = lhs->get_field(one_criteria);
            const auto rhs_field_value = rhs->get_field(one_criteria);

            if(lhs_field_value != rhs_field_value) {
                return lhs_field_value < rhs_field_value;
            }
        }

        return false;
    });
}

void PasswordManager::add_password() noexcept {
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

            std::cout << "The strength of the password is: " << PasswordStrength::to_string(
                    Password::check_password_strength(password)) << std::endl;

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

void PasswordManager::edit_password() noexcept {
    std::cout << "========== PASSWORDS ==========" << std::endl;
    for (int i = 0; i < passwords.size(); ++i) {
        std::cout << (i + 1) << ". " << *passwords[i] << std::endl;
    }

    std::cout << "Which password do you want to edit? Enter number (0 to cancel): ";
    auto user_choice {-1};
    std::cin >> user_choice; std::cin.get();

    if(user_choice < 1 || user_choice > passwords.size()) {
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

void PasswordManager::remove_passwords() {
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

    auto to_erase = std::ranges::remove_if(passwords_to_remove, [this](const auto& number) {
        return number < 0 || number >= passwords.size();
    });
    passwords_to_remove.erase(to_erase.begin(), to_erase.end());

    std::ranges::sort(passwords_to_remove);

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

void PasswordManager::add_category() noexcept {
    std::cout << "========== ADDING CATEGORY ==========" << std::endl;
    std::cout << "Provide category name: ";
    auto category_name = std::string();
    std::getline(std::cin, category_name);

    if(do_category_exists(category_name)) {
        std::cout << "Category with this name already exists!" << std::endl;
        return;
    }

    categories.emplace(Utilities::to_lowercase(category_name));
    std::cout << "Category added successfully!" << std::endl;
}

void PasswordManager::remove_category() noexcept {
    std::cout << "========== REMOVING CATEGORY ==========" << std::endl;
    std::cout << "Provide category name: ";
    auto category_name = std::string();
    std::getline(std::cin, category_name);

    if(!do_category_exists(category_name)) {
        std::cout << "Category with this name does not exist!" << std::endl;
        return;
    }

    categories.erase(Utilities::to_lowercase(category_name));
    std::cout << "Category removed successfully!" << std::endl;

    // Remove all passwords that were in this category
    auto to_erase = std::ranges::remove_if(passwords, [&category_name](const auto& password) {
        return password->get_field(password_field::CATEGORY) == category_name;
    });

    passwords.erase(to_erase.begin(), to_erase.end());
}

void PasswordManager::menu() noexcept {
    auto choice {0};

    while(true) {
        std::cout << "========== MAIN MENU ==========" << std::endl;
        std::cout << "1. Show all passwords" << std::endl;
        std::cout << "2. Show passwords that match the given criteria" << std::endl;
        std::cout << "3. Sort passwords" << std::endl;
        std::cout << "4. Add password" << std::endl;
        std::cout << "5. Edit password" << std::endl;
        std::cout << "6. Remove passwords" << std::endl;
        std::cout << "7. Add category" << std::endl;
        std::cout << "8. Remove category" << std::endl;
        std::cout << "9. Save changes and exit" << std::endl;

        std::cout << "Your choice: ";
        std::cin >> choice; std::cin.get();

        system("cls");
        switch(choice) {
            case 1:
                system("cls");
                std::cout << "========== PASSWORDS ==========" << std::endl;

                if(passwords.empty()) {
                    std::cout << "No passwords to show!" << std::endl;
                    break;
                }

                std::ranges::for_each(passwords, [](const auto& password) {
                    std::cout << *password << std::endl;
                });

                break;
            case 2:
                {
                    auto criteria_passwords = get_passwords();

                    system("cls");
                    std::cout << "========== PASSWORDS ==========" << std::endl;

                    if(criteria_passwords.empty()) {
                        std::cout << "No passwords match the given criteria!" << std::endl;
                        break;
                    }

                    std::ranges::for_each(criteria_passwords, [](const auto& password) {
                        std::cout << *password << std::endl;
                    });
                }
                break;
            case 3:
                sort_passwords(PasswordManager::get_criteria_from_user());
                std::cout << "The passwords have been sorted successfully!" << std::endl;
                break;
            case 4:
                add_password();
                break;
            case 5:
                edit_password();
                break;
            case 6:
                remove_passwords();
                break;
            case 7:
                add_category();

                system("cls");
                std::cout << "The categories are now: " << get_categories_string() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                system("cls");

                break;
            case 8:
                remove_category();
                break;
            case 9:
                FileWriter::save(
                        path_to_file_with_passwords,
                        add_timestamp_to_vector(generate_encrypted_output_vector())
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