#include "core/password_core.h"
#include "core/ps_core_abi.h"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

std::string PasswordCore::generate_password(int length) const {
    if (length <= 0) {
        throw std::runtime_error("Error: Password length must be positive.");
    }

    std::vector<char> buffer(static_cast<std::size_t>(length) + 1, '\0');
    const int code = ps_generate_password(length, buffer.data(), buffer.size());
    if (code != 0) {
        throw std::runtime_error("Error: Rust core failed to generate password (code " + std::to_string(code) + ").");
    }
    return std::string(buffer.data());
}
