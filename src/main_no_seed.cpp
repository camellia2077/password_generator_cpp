// File: main_no_seed.cpp
#include "password_utils.h"
#include "cmd_parser.h" // Include the new parser module
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        // 1. Call the parser to get configuration
        PasswordArgs args = parse_arguments(argc, argv);

        // Handle help request
        if (args.help_requested) {
            show_usage(argv[0]);
            return 0;
        }

        const std::string filename = "password_unseeded.txt";
        std::ofstream outfile(filename);

        if (!outfile.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
            return 1;
        }

        std::cout << "Generating " << args.count << " password(s) of length " 
                  << args.length << " (using random_device)..." << std::endl;

        // 2. Use the parsed arguments
        for (int i = 0; i < args.count; ++i) {
            std::string new_password = generatePasswordWithDevice(args.length);
            std::cout << new_password << std::endl;
            outfile << new_password << std::endl;
        }

        std::cout << "\nSuccessfully saved " << args.count << " password(s) to " << filename << std::endl;

    } catch (const std::runtime_error& e) {
        // 3. Catch any errors from the parser
        std::cerr << e.what() << std::endl;
        show_usage(argv[0]);
        return 1;
    }

    return 0;
}