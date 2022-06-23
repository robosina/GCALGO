include(FetchContent)
set(FETCHCONTENT_QUIET off)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/externals)

#
# googletest dependency
#
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    message(STATUS "Fetching googletest...")
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    set_property(TARGET gtest gmock APPEND PROPERTY COMPILE_OPTIONS "-w")
endif ()

#
# rapid json dependency
#
set(GOOGLE_TEST_VERSION 1.9.0)
FetchContent_Declare(
        rapidjson
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG master
        CMAKE_ARGS
        -DRAPIDJSON_BUILD_TESTS=OFF
        -DRAPIDJSON_BUILD_DOC=OFF
        -DRAPIDJSON_BUILD_EXAMPLES=OFF
)
FetchContent_GetProperties(rapidjson)
if (NOT rapidjson_POPULATED)
    message(STATUS "Fetching rapidjson...")
    FetchContent_Populate(rapidjson)
    include_directories(${rapidjson_SOURCE_DIR}/include)
endif ()