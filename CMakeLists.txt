# CMake minimum version required
cmake_minimum_required(VERSION 3.13)

# Project Name
project(PasswordGenerators CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 1. Create a library from the shared utility files located in the src directory.
add_library(password_lib src/password_utils.cpp src/cmd_parser.cpp)

# 2. Add the executable for the program that uses the device directly.
add_executable(password_generator_cpp src/main_no_seed.cpp)

# 3. Link the shared library to the executable.
target_link_libraries(password_generator_cpp PRIVATE password_lib)

# 4. Add compiler options to all targets for optimization.
# -Os:         Optimize for size. 
# -flto:       Enable Link-Time Optimization. 
# -march=native: Optimize for the specific CPU architecture of the build machine.
target_compile_options(password_lib PRIVATE -Os -flto -march=native)
target_compile_options(password_generator_cpp PRIVATE -Os -flto -march=native)

# 5. Add linker options to the final executable.
# -s: Strip all symbol tables.
target_link_options(password_generator_cpp PRIVATE -s)