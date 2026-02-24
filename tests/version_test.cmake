if(NOT DEFINED EXE_PATH)
    message(FATAL_ERROR "EXE_PATH is required.")
endif()

if(NOT EXISTS "${EXE_PATH}")
    message(FATAL_ERROR "Executable not found: ${EXE_PATH}")
endif()

if(NOT DEFINED EXPECTED_VERSION)
    message(FATAL_ERROR "EXPECTED_VERSION is required.")
endif()

execute_process(
    COMMAND "${EXE_PATH}" --version
    RESULT_VARIABLE RUN_RESULT
    OUTPUT_VARIABLE RUN_STDOUT
    ERROR_VARIABLE RUN_STDERR
)

if(NOT RUN_RESULT EQUAL 0)
    message(FATAL_ERROR
        "Version command failed with code ${RUN_RESULT}\n"
        "stdout:\n${RUN_STDOUT}\n"
        "stderr:\n${RUN_STDERR}\n")
endif()

string(REPLACE "\r\n" "\n" RUN_STDOUT "${RUN_STDOUT}")
string(REPLACE "\r" "\n" RUN_STDOUT "${RUN_STDOUT}")
string(REGEX REPLACE "\n+$" "" RUN_STDOUT "${RUN_STDOUT}")

set(EXPECTED_LINE "password_generator_cpp ${EXPECTED_VERSION}")
if(NOT RUN_STDOUT STREQUAL EXPECTED_LINE)
    message(FATAL_ERROR
        "Unexpected version output.\n"
        "expected: ${EXPECTED_LINE}\n"
        "actual:   ${RUN_STDOUT}")
endif()

if(NOT RUN_STDERR STREQUAL "")
    message(FATAL_ERROR "Expected empty stderr, got:\n${RUN_STDERR}")
endif()

message(STATUS "Version test passed.")
