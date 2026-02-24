#include "io/password_file_io.h"

#include <fstream>

bool save_passwords_to_file(
    const std::vector<std::string>& passwords,
    const std::string& filename,
    std::string& error_message) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        error_message = "Error: Could not open file " + filename + " for writing.";
        return false;
    }

    for (const std::string& password : passwords) {
        outfile << password << '\n';
    }

    return true;
}
