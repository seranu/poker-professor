cmake_minimum_required(VERSION 2.8.9)

set(TOP_DIR ${CMAKE_SOURCE_DIR})
project(poker-professor)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(WARNING "build is release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall")
endif()

enable_testing()
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 17)

include_directories(poker-professor
    include
    include/base
    include/equity
    include/utility)
add_library(professor STATIC
    src/base/deck.cpp
    src/base/random.cpp
    src/base/card.cpp
    src/base/hand_value.cpp
    src/base/dealer.cpp
    src/base/board.cpp
    src/base/player.cpp
    src/utility/debug.cpp
    src/utility/log.cpp
    src/equity/equity_calculator.cpp
    src/poker_solver.cpp
    )

link_libraries(professor)
add_executable(poker-professor
    professor.cpp)
