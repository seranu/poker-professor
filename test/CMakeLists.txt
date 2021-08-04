project(unittest)
include_directories(unittest
    ${TOP_DIR}/include
    ${TOP_DIR}/third-party/catch2)

add_executable(unittest
    card_test.cpp
    test_main.cpp)

target_link_libraries(unittest professor)

#add_custom_command(
#    TARGET unittest
#    COMMENT "Running tests"
#    POST_BUILD
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#    COMMAND ./test/unittest
#)

add_custom_target(run-unittests unittest COMMAND $<TARGET_FILE:unittest> DEPENDS unittest)
add_test(NAME test COMMAND ./test/unittest WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
