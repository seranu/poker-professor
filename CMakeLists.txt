cmake_minimum_required(VERSION 2.8.9)

set(TOP_DIR ${CMAKE_SOURCE_DIR})
project(poker-professor)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

enable_testing()
add_subdirectory(test)

set(CMAKE_CXX_STANDARD 17)

include_directories(poker-professor
    include)
add_library(professor STATIC
    src/deck.cpp
    src/random.cpp
    src/card.cpp
    src/poker_solver.cpp
    src/debug.cpp
    src/hand_value.cpp
    src/player.cpp
    src/dealer.cpp
    src/board.cpp
    )

link_libraries(professor)
add_executable(poker-professor
    professor.cpp)
