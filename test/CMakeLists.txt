project(unittest)
include_directories(unittest
    ${TOP_DIR}/include
    ${TOP_DIR}/third-party/catch2)

add_executable(unittest
    card_test.cpp
    test_main.cpp)

add_custom_command(
    TARGET unittest
    COMMENT "Running tests"
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)