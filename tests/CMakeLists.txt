project(tests)

file(GLOB_RECURSE TEST_SOURCES *.cpp)
file(GLOB_RECURSE TEST_HEADERS *.h)
file(GLOB_RECURSE MAIN_SOURCES "../src/*.cpp" "../src/*.h")
add_executable(tests main.cpp ${TEST_SOURCES} ${TEST_HEADERS} ${MAIN_SOURCES})

target_link_libraries(tests
        PRIVATE
        gtest
        )
