cmake_minimum_required(VERSION 3.21)
project(greedy_construction)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(FetchDependencies)

file(GLOB_RECURSE EXTRA_SOURCES "./src/*.h" "./src/*.cpp")

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/src/report
        )
add_executable(greedy_construction main.cpp ${EXTRA_SOURCES})
add_subdirectory(tests)