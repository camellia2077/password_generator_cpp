# CMake minimum version required
cmake_minimum_required(VERSION 3.13)

# Project Name
project(PasswordGenerators CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(password_app_lib
    src/cmd_parser.cpp
    src/core/password_core.cpp
    src/io/password_file_io.cpp
    src/presentation/password_app.cpp
)
target_include_directories(password_app_lib PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(password_generator_cpp src/main.cpp)
target_link_libraries(password_generator_cpp PRIVATE password_app_lib)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(password_app_lib PRIVATE -Os -flto -march=native)
    target_compile_options(password_generator_cpp PRIVATE -Os -flto -march=native)
    target_link_options(password_generator_cpp PRIVATE -s)
endif()

if(WIN32)
    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(FATAL_ERROR "GNU static mode requires a GNU C++ compiler on Windows.")
    endif()

    find_program(CARGO_EXECUTABLE cargo REQUIRED)
    set(RUST_TARGET x86_64-pc-windows-gnu)
    set(RUST_CORE_MANIFEST ${CMAKE_SOURCE_DIR}/src/rust_core/Cargo.toml)
    set(RUST_CORE_STATIC_LIB ${CMAKE_SOURCE_DIR}/src/rust_core/target/${RUST_TARGET}/release/libps_core.a)

    add_custom_command(
        OUTPUT ${RUST_CORE_STATIC_LIB}
        COMMAND ${CARGO_EXECUTABLE} build --release --target ${RUST_TARGET} --manifest-path ${RUST_CORE_MANIFEST}
        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/rust_core/Cargo.toml
            ${CMAKE_SOURCE_DIR}/src/rust_core/Cargo.lock
            ${CMAKE_SOURCE_DIR}/src/rust_core/src/lib.rs
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Building Rust core static library (libps_core.a)"
        VERBATIM
    )

    add_custom_target(ps_core_static ALL DEPENDS ${RUST_CORE_STATIC_LIB})
    add_dependencies(password_app_lib ps_core_static)

    target_link_libraries(password_app_lib PRIVATE ${RUST_CORE_STATIC_LIB} bcrypt ntdll)
    target_link_options(password_generator_cpp PRIVATE -static -static-libgcc -static-libstdc++)
endif()

enable_testing()
add_test(
    NAME smoke_runtime
    COMMAND ${CMAKE_COMMAND}
        -DEXE_PATH=$<TARGET_FILE:password_generator_cpp>
        -DWORK_DIR=${CMAKE_BINARY_DIR}/tests/smoke
        -P ${CMAKE_SOURCE_DIR}/tests/smoke_test.cmake
)

add_test(
    NAME version_flag
    COMMAND ${CMAKE_COMMAND}
        -DEXE_PATH=$<TARGET_FILE:password_generator_cpp>
        -DEXPECTED_VERSION=0.1.0
        -P ${CMAKE_SOURCE_DIR}/tests/version_test.cmake
)
