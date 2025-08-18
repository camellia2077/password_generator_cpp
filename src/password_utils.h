// File: password_utils.h
#ifndef PASSWORD_UTILS_H
#define PASSWORD_UTILS_H

#include <string>

// --- Function Declarations ---

/**
 * @brief Generates a password using std::mt19937 seeded by std::random_device.
 * @param length The desired length of the password.
 * @return The generated password string.
 */
std::string generatePasswordWithSeededMT(int length);

/**
 * @brief Generates a password using std::random_device directly.
 * @param length The desired length of the password.
 * @return The generated password string.
 */
std::string generatePasswordWithDevice(int length);

/**
 * @brief Saves a given password to a specified file, overwriting any existing content.
 * @param password The password string to save.
 * @param filename The name of the file to save to.
 * @return True if saving was successful, false otherwise.
 */
bool savePasswordToFile(const std::string& password, const std::string& filename);

#endif // PASSWORD_UTILS_H