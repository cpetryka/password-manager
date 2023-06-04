# PASSWORD MANAGER
**Author: Cezary Petryka**

**It's a console application for modifying and reading from a file that stores our passwords along with additional information about various websites to which these passwords relate. Files in which passwords are stored are encrypted with a single main password.** The application is launched from the command line and execute the appropriate functions based on commands read from the keyboard, returning the relevant information in a command-line interface (CLI) style.

**Upon launching the program, the user is able to choose one of the files located in the program’s folder or provide a direct, absolute path to the file.**

**Each attempt to decrypt the file saves a timestamp of that operation.**

**Each password contains at least:**
- Name (The name of this entry, e.g. “Password for Account1 on Google”)
- Text representing the password
- Category

**Each password may additionally contain:**
- Website / Service
- Login

Available commands:
1. **Search passwords** - returns passwords that contain specific parameters.
2. **Sort passwords** - returns a sorted list of all passwords. It allows sorting by a few different parameters at the same time, such as by name and category.
3. **Add password** - adds a new password to the encrypted file. The user is given the option to enter their own password and informed about how secure the password is and whether it has been used before. Additionally, an automatically generated password is proposed to the user, giving them the option to choose certain parameters such as:
   - Number of characters; 
   - Whether to include uppercase and lowercase letters; 
   - Whether to include special characters.
4. **Edit password** - allows editing of data in an existing password.
5. **Delete password(s)** - deletes the selected password or passwords.
6. **Add category** - adds a new category that we can use when creating new passwords.
7. **Delete category** - deletes the category along with all the passwords assigned to that category.