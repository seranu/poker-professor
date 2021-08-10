project(unittest)
include_directories(unittest
    ${TOP_DIR}/include
    ${TOP_DIR}/include/base
    ${TOP_DIR}/include/equity
    ${TOP_DIR}/include/utility
    ${TOP_DIR}/third-party/catch2)

set(CMAKE_CXX_STANDARD 17)

add_executable(unittest
    card_test.cpp
    hand_value_test.cpp
    poker_solver_test.cpp
    test_main.cpp)

target_link_libraries(unittest professor)
