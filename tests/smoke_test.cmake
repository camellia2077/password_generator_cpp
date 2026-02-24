if(NOT DEFINED EXE_PATH)
    message(FATAL_ERROR "EXE_PATH is required.")
endif()

if(NOT EXISTS "${EXE_PATH}")
    message(FATAL_ERROR "Executable not found: ${EXE_PATH}")
endif()

if(NOT DEFINED WORK_DIR)
    set(WORK_DIR "${CMAKE_BINARY_DIR}/tests/smoke")
endif()

file(MAKE_DIRECTORY "${WORK_DIR}")
set(PASSWORD_FILE "${WORK_DIR}/passwords.txt")
file(REMOVE "${PASSWORD_FILE}")

execute_process(
    COMMAND "${EXE_PATH}" -n 3 -l 12
    WORKING_DIRECTORY "${WORK_DIR}"
    RESULT_VARIABLE RUN_RESULT
    OUTPUT_VARIABLE RUN_STDOUT
    ERROR_VARIABLE RUN_STDERR
)

if(NOT RUN_RESULT EQUAL 0)
    message(FATAL_ERROR
        "Executable failed with code ${RUN_RESULT}\n"
        "stdout:\n${RUN_STDOUT}\n"
        "stderr:\n${RUN_STDERR}\n")
endif()

if(NOT EXISTS "${PASSWORD_FILE}")
    message(FATAL_ERROR "Expected output file not found: ${PASSWORD_FILE}")
endif()

file(READ "${PASSWORD_FILE}" PASSWORD_FILE_CONTENT)
string(REPLACE "\r\n" "\n" PASSWORD_FILE_CONTENT "${PASSWORD_FILE_CONTENT}")
string(REPLACE "\r" "\n" PASSWORD_FILE_CONTENT "${PASSWORD_FILE_CONTENT}")

if(PASSWORD_FILE_CONTENT STREQUAL "")
    message(FATAL_ERROR "passwords.txt is empty.")
endif()

set(PASSWORD_CHARS_ONLY "${PASSWORD_FILE_CONTENT}")
string(REPLACE "\n" "" PASSWORD_CHARS_ONLY "${PASSWORD_CHARS_ONLY}")
string(LENGTH "${PASSWORD_CHARS_ONLY}" PASSWORD_CHARS_COUNT)

set(PASSWORD_NEWLINES_ONLY "${PASSWORD_FILE_CONTENT}")
string(REGEX REPLACE "[^\n]" "" PASSWORD_NEWLINES_ONLY "${PASSWORD_NEWLINES_ONLY}")
string(LENGTH "${PASSWORD_NEWLINES_ONLY}" PASSWORD_NEWLINE_COUNT)

if(NOT PASSWORD_CHARS_COUNT EQUAL 36 OR NOT PASSWORD_NEWLINE_COUNT EQUAL 3)
    message(FATAL_ERROR
        "Expected 3 passwords of length 12 (36 chars) and 3 newline separators.\n"
        "File content:\n${PASSWORD_FILE_CONTENT}")
endif()

if(NOT RUN_STDOUT MATCHES "Successfully saved 3 password\\(s\\) to passwords\\.txt")
    message(FATAL_ERROR
        "Expected success line not found in stdout.\nstdout:\n${RUN_STDOUT}")
endif()

message(STATUS "Smoke test passed.")
