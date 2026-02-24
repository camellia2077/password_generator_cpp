#ifndef PASSWORD_FILE_IO_H
#define PASSWORD_FILE_IO_H

#include <string>
#include <vector>

bool save_passwords_to_file(
    const std::vector<std::string>& passwords,
    const std::string& filename,
    std::string& error_message);

#endif // PASSWORD_FILE_IO_H
