// File: main_seeded.cpp
#include "password_utils.h" // Include the shared functions
#include <iostream>

int main() {
    const int password_length = 20;
    
    // Call the specific generator function from the utility library
    std::string new_password = generatePasswordWithSeededMT(password_length);

    std::cout << "Generated Password (with seeded mt19937): " << new_password << std::endl;

    // Call the shared save function
    savePasswordToFile(new_password, "password_seeded.txt");

    return 0;
}