// File: password_utils.cpp
#include "password_utils.h"
#include <iostream>
#include <random>
#include <fstream>

// --- Shared Constants ---
const std::string ALL_CHARS =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!@#$%^&*()_+-=[]{}|;:',.<>/?";

// --- Function Definitions ---

std::string generatePasswordWithSeededMT(int length) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(ALL_CHARS.length()) - 1);

    std::string password;
    password.reserve(length);
    for (int i = 0; i < length; ++i) {
        password += ALL_CHARS[distribution(generator)];
    }
    return password;
}

std::string generatePasswordWithDevice(int length) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, static_cast<int>(ALL_CHARS.size()) - 1);

    std::string password;
    password.reserve(length);
    for (int i = 0; i < length; i++) {
        password += ALL_CHARS[dist(rd)];
    }
    return password;
}

bool savePasswordToFile(const std::string& password, const std::string& filename) {
    std::ofstream outfile(filename); // Defaults to overwriting
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    outfile << password << std::endl;
    std::cout << "Password successfully saved to " << filename << std::endl;
    return true;
}