// File: cmd_parser.h
#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#include <string>

/**
 * @brief Holds the configuration parsed from command-line arguments.
 */
struct PasswordArgs {
    int count = 1;      // Number of passwords to generate
    int length = 20;    // Length of each password
    bool help_requested = false; // Flag if the user asked for help
};

/**
 * @brief Parses command-line arguments (argc, argv) to configure password generation.
 * * @param argc The argument count from main().
 * @param argv The argument vector from main().
 * @return A PasswordArgs struct populated with the parsed values or defaults.
 * @throws std::runtime_error if a required value is missing or invalid.
 */
PasswordArgs parse_arguments(int argc, char* argv[]);

/**
 * @brief Prints the usage instructions for the program.
 * * @param program_name The name of the executable (argv[0]).
 */
void show_usage(const std::string& program_name);

#endif // CMD_PARSER_H