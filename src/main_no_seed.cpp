// File: main_no_seed.cpp
#include "password_utils.h" // Include the shared functions
#include <iostream>

int main() {
    const int password_length = 20;

    // Call the specific generator function from the utility library
    std::string new_password = generatePasswordWithDevice(password_length);

    std::cout << "Generated Password (no explicit seed): " << new_password << std::endl;

    // Call the shared save function
    savePasswordToFile(new_password, "password_unseeded.txt");

    return 0;
}