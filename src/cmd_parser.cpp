// File: cmd_parser.cpp
#include "cmd_parser.h"
#include <iostream>
#include <stdexcept>
#include <string>

void show_usage(const std::string& program_name) {
    // Update the usage text to show the new long options
    std::cerr << "Usage: " << program_name << " [options]\n"
              << "Options:\n"
              << "\t-h, --help\t\tShow this help message\n"
              << "\t-n, --num <count>\tNumber of passwords to generate (default: 1)\n"
              << "\t-l, --length <length>\tLength of each password (default: 20)\n"
              << std::endl;
}

PasswordArgs parse_arguments(int argc, char* argv[]) {
    PasswordArgs args; // Initialize with default values

    try {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-h" || arg == "--help") {
                args.help_requested = true;
                return args; // Exit early if help is requested
            } else if (arg == "-n" || arg == "--num") { // Add check for --num
                if (i + 1 < argc) {
                    args.count = std::stoi(argv[++i]);
                } else {
                    // Throw an exception instead of printing directly
                    throw std::runtime_error("Error: " + arg + " option requires one argument.");
                }
            } else if (arg == "-l" || arg == "--length") { // Add check for --length
                if (i + 1 < argc) {
                    args.length = std::stoi(argv[++i]);
                } else {
                    throw std::runtime_error("Error: " + arg + " option requires one argument.");
                }
            }
        }
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Error: Invalid number format for --num or --length.");
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Error: Number out of range for --num or --length.");
    }

    if (args.length <= 0 || args.count <= 0) {
        throw std::runtime_error("Error: Password count and length must be positive numbers.");
    }

    return args;
}