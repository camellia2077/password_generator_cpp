#include "presentation/password_app.h"

#include "cmd_parser.h"
#include "core/password_core.h"
#include "io/password_file_io.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
const char* kOutputFilename = "passwords.txt";
}

int run_password_app(int argc, char* argv[]) {
    PasswordArgs args;
    try {
        args = parse_arguments(argc, argv);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        show_usage(argv[0]);
        return 1;
    }

    if (args.help_requested) {
        show_usage(argv[0]);
        return 0;
    }

    if (args.version_requested) {
        show_version();
        return 0;
    }

    try {
        PasswordCore core;
        std::vector<std::string> passwords;
        passwords.reserve(static_cast<std::size_t>(args.count));

        for (int i = 0; i < args.count; ++i) {
            std::string new_password = core.generate_password(args.length);
            std::cout << "Generated Password #" << (i + 1) << ": " << new_password << std::endl;
            passwords.push_back(new_password);
        }

        std::string error_message;
        if (!save_passwords_to_file(passwords, kOutputFilename, error_message)) {
            std::cerr << error_message << std::endl;
            return 1;
        }

        std::cout << "\nSuccessfully saved " << passwords.size()
                  << " password(s) to " << kOutputFilename << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
