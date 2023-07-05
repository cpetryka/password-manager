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

        criteria.emplace_back(choice);

        auto answer = std::string {};

        do {
            std::cout << "Do you want to add another criteria? (y/n): ";
            std::getline(std::cin, answer);
        } while(answer != "y" && answer != "n");

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

        auto answer = std::string {};

        do {
            std::cout << "Do you want to add another criteria? (y/n): ";
            std::getline(std::cin, answer);
        } while(answer != "y" && answer != "n");

        if(answer == "n") {
            break;
        }
    }

    return criteria;
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

void PasswordManager::refresh_categories_set() noexcept {
    // Clear the set because there might be some old categories that are no longer in use
    categories.clear();

    for (const auto& password_ptr : passwords) {
        categories.emplace(Utilities::to_lowercase(password_ptr->get_field(password_field::CATEGORY)));
    }
}

bool PasswordManager::check_if_password_has_already_been_used(const std::string& password) const noexcept {
    return std::ranges::any_of(passwords, [&password](const auto& password_ptr) {
        return password_ptr->compare_field_with(password_field::PASSWORD, password);
    });
}

void PasswordManager::remove_passwords_at_indexes(std::vector<int> &indexes) {
    std::ranges::sort(indexes);

    // We need to remove the passwords from the end, because if we remove them from the beginning, the indexes
    // of the remaining passwords will change
    for(auto it = indexes.rbegin(); it != indexes.rend(); ++it) {
        passwords.erase(passwords.begin() + *it);
    }
}

std::vector<std::string> PasswordManager::generate_encrypted_output_vector() const noexcept {
    auto result = std::vector<std::string> {};

    std::ranges::for_each(passwords, [&](const auto& password_ptr) {
        result.emplace_back(Encryptor::encrypt(password_ptr->get_raw_string(SEPARATOR), master_password));
    });

    return result;
}

std::vector<std::string> PasswordManager::add_timestamp_to_vector(const std::vector<std::string>& vector, const std::string& last_decryption) noexcept {
    auto result = std::vector<std::string> {vector};
    auto timestamp_copy = last_decryption;

    // If there is fewer than 8 elements in the vector, then we need to add empty strings to the vector
    while(result.size() < 8) {
        result.emplace_back("");
    }

    // Add the timestamp to the vector
    for(auto i = 1; i < 8; i += 2) {
        result.at(i) = timestamp_copy.substr(0, 4) + result.at(i);
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

fs::path PasswordManager::get_path_to_file_with_passwords_from_user() const {
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
                            continue;
                        }

                        break;
                    }

                    do_continue = {false};
                    break;
                }
            case 2:
                // Check if the directory exists and create it if it doesn't
                if(!FileManager::check_if_directory_exists(SAVED_PASSWORDS_PATH)) {
                    create_directory(SAVED_PASSWORDS_PATH);
                }

                // Check if the directory is empty, if it is, print a message and go back to the menu
                if(FileManager::check_if_directory_is_empty(SAVED_PASSWORDS_PATH)) {
                    std::cout << "There are no saved files. Create one first!" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    system("cls");
                    continue;
                }

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
                std::this_thread::sleep_for(std::chrono::seconds(2));
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
        auto vector_with_timestamp = add_timestamp_to_vector(encrypted_file_content, last_decryption_timestamp);

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
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        // Decryption of the file
        auto pair = get_password_and_try_decrypt();

        if(pair.second.empty()) {
            system("cls");
            std::cout << "Something went wrong. Try again!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        // If the decryption was successful, then we can assign master password and the passwords vector and break the loop
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

std::vector<std::unique_ptr<Password>> PasswordManager::get_passwords(const std::vector<std::pair<password_field, std::string>>& criteria) noexcept {
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

bool PasswordManager::sort_passwords(const std::vector<password_field> &criteria) noexcept {
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

    return true;
}

bool PasswordManager::add_password() noexcept {
    std::cout << "========== ADDING NEW PASSWORD ==========" << std::endl;

    // Description of the password
    std::cout << "Provide description: ";
    auto description = std::string {};
    std::getline(std::cin, description);

    // Password of the password
    auto user_choice {-1};

    do {
        std::cout << "Do you want to provide your own password (enter 1) or generate one (enter 2): ";
        std::cin >> user_choice; std::cin.get();
    } while(user_choice != 1 && user_choice != 2);

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

            auto answer = std::string {};

            do {
                std::cout << "Do you want to provide another password? (y/n): ";
                std::getline(std::cin, answer);
            } while(answer != "y" && answer != "n");

            if(answer == "n") {
                do_continue = false;
            }
        }
    }
    else if(user_choice == 2) {
        auto number_of_characters {-1};

        do {
            std::cout << "How many characters should the password have? (min 8): ";
            std::cin >> number_of_characters; std::cin.get();
        } while(number_of_characters < 8);

        auto answer = std::string {};

        do {
            std::cout << "Should the password contain upper and lower case letters? (y/n): ";
            std::getline(std::cin, answer);
        } while(answer != "y" && answer != "n");

        auto answer2 = std::string {};

        do {
            std::cout << "Should the password contain special characters? (y/n): ";
            std::getline(std::cin, answer2);
        } while(answer2 != "y" && answer2 != "n");

        password = Password::generate_password(number_of_characters, answer == "y", answer2 == "y");
    }
    else {
        std::cout << "There is no such option! Exiting..." << std::endl;
        return false;
    }

    // Category of the password
    std::cout << "Available categories: " << get_categories_string() << std::endl;

    auto category = std::string {};

    do {
        std::cout << "Provide category: " << std::endl;
        std::getline(std::cin, category);
    } while(!do_category_exists(category));

    // Website address of the password
    auto website_address = std::string {};

    do {
        std::cout << "Provide website address (enter '-' if you do not want to provide a login): ";
        std::getline(std::cin, website_address);
    } while(!PasswordValidator::is_website_address_valid(website_address));

    // Login of the password
    std::cout << "Provide login (enter '-' if you do not want to provide a login): ";
    auto login = std::string {};
    std::getline(std::cin, login);

    passwords.emplace_back(std::make_unique<Password>(description, password, category, website_address, login));
    return true;
}

bool PasswordManager::edit_password() noexcept {
    // Print all passwords
    std::cout << "========== PASSWORDS ==========" << std::endl;
    for (int i = 0; i < passwords.size(); ++i) {
        std::cout << (i + 1) << ". " << *passwords[i] << std::endl;
    }

    // Choose password to edit
    auto user_choice {-1};

    do {
        std::cout << "Which password do you want to edit? Enter number (0 to cancel): ";
        std::cin >> user_choice; std::cin.get();
    } while(user_choice < 0 || user_choice > passwords.size());

    if(user_choice == 0) {
        std::cout << "Cancelling..." << std::endl;
        return false;
    }

    // Let user choose field to edit
    std::cout << "========== EDITING PASSWORD ==========" << std::endl;
    std::cout << "Which field do you want to edit?" << std::endl;
    auto field = PasswordField::choose_field_menu();

    // Edit field (user can try to edit field 3 times)
    auto new_value = std::string();
    auto i = 0;

    do {
        if(i == 3) {
            std::cout << "You have entered invalid value 3 times. Cancelling..." << std::endl;
            return false;
        }

        if(i++ > 0) {
            std::cout << "Invalid value!" << std::endl;
        }

        std::cout << "Provide new value: ";
        std::getline(std::cin, new_value);
    } while (!passwords[user_choice - 1]->edit_password(field, new_value));

    return true;
}

bool PasswordManager::remove_passwords() {
    // Print all passwords
    std::cout << "========== PASSWORDS ==========" << std::endl;
    for (int i = 0; i < passwords.size(); ++i) {
        std::cout << (i + 1) << ". " << *passwords[i] << std::endl;
    }

    // Ask the user which passwords they want to remove
    auto user_choice = std::string();

    do {
        std::cout << "Which passwords do you want to remove? Enter numbers separated by spaces (0 to cancel): ";
        std::getline(std::cin, user_choice);
    } while(!std::regex_match(user_choice, std::regex("\\d+( \\d+)*")));

    if(user_choice == "0") {
        return false;
    }

    // Ask the user if they are sure they want to remove the passwords
    auto do_remove = std::string();

    do {
        std::cout << "Are you sure you want to remove selected passwords? (y/n): ";
        std::getline(std::cin, do_remove);
    } while(do_remove != "y" && do_remove != "n");

    if(do_remove == "n") {
        return false;
    }

    // Convert the user's choice to a vector of numbers
    auto passwords_to_remove = Utilities::split_to_numbers(user_choice, " ");

    // We need to subtract 1 from each number
    std::ranges::transform(passwords_to_remove, passwords_to_remove.begin(), [](const auto& number) {
        return number - 1;
    });

    // Remove all numbers that are out of range
    auto to_erase = std::ranges::remove_if(passwords_to_remove, [this](const auto& number) {
        return number < 0 || number >= passwords.size();
    });
    passwords_to_remove.erase(to_erase.begin(), to_erase.end());

    // Remove the passwords
    remove_passwords_at_indexes(passwords_to_remove);

    return true;
}

bool PasswordManager::add_category() noexcept {
    // Ask the user for the category name to add
    std::cout << "========== ADDING CATEGORY ==========" << std::endl;
    std::cout << "Provide category name to add: ";
    auto category_name = std::string();
    std::getline(std::cin, category_name);

    // Check if the category already exists
    if(do_category_exists(category_name)) {
        std::cout << "Category with this name already exists!" << std::endl;
        return false;
    }

    // Add the category to the set
    categories.emplace(Utilities::to_lowercase(category_name));

    return true;
}

bool PasswordManager::remove_category() noexcept {
    // It's not possible to remove a category if there are no categories
    if(categories.empty()) {
        std::cout << "There are no categories to remove!" << std::endl;
        return false;
    }

    // Print all categories and ask the user which one to remove
    std::cout << "========== REMOVING CATEGORY ==========" << std::endl;
    std::cout << "Available categories: " << get_categories_string() << std::endl;
    std::cout << "Provide category name to remove: ";
    auto category_name = std::string();
    std::getline(std::cin, category_name);

    // Check if the category exists
    if(!do_category_exists(category_name)) {
        std::cout << "Category with this name does not exist!" << std::endl;
        return false;
    }

    // Remove category from the set
    categories.erase(Utilities::to_lowercase(category_name));

    // Remove all passwords that have this category
    auto to_erase = std::ranges::remove_if(passwords, [&category_name](const auto& password) {
        return password->compare_field_with(password_field::CATEGORY, category_name);
    });
    passwords.erase(to_erase.begin(), to_erase.end());

    return true;
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
                    auto criteria_passwords = get_passwords(get_extended_criteria_from_user());

                    system("cls");
                    std::cout << "========== PASSWORDS ==========" << std::endl;

                    if(criteria_passwords.empty()) {
                        std::cout << "No passwords to show!" << std::endl;
                        break;
                    }

                    std::ranges::for_each(criteria_passwords, [](const auto& password) {
                        std::cout << *password << std::endl;
                    });
                }
                break;
            case 3:
                if(sort_passwords(PasswordManager::get_criteria_from_user())) {
                    std::cout << "The passwords have been sorted successfully!" << std::endl;
                }
                break;
            case 4:
                if(add_password()) {
                    std::cout << "Password has been added successfully!" << std::endl;
                }
                break;
            case 5:
                if(edit_password()) {
                    std::cout << "Password has been edited successfully!" << std::endl;
                }
                break;
            case 6:
                if(remove_passwords()) {
                    std::cout << "Passwords removed successfully!" << std::endl;
                }
                break;
            case 7:
                if(add_category()) {
                    std::cout << "Category added successfully!" << std::endl;
                    std::cout << "The categories are now: " << get_categories_string() << std::endl;
                }
                break;
            case 8:
                if(remove_category()) {
                    std::cout << "Category removed successfully!" << std::endl;
                    std::cout << "The categories are now: " << get_categories_string() << std::endl;
                }
                break;
            case 9:
                FileWriter::save(
                        path_to_file_with_passwords,
                        add_timestamp_to_vector(generate_encrypted_output_vector(), last_decryption_timestamp)
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