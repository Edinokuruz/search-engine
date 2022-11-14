cmake_minimum_required (VERSION 3.21)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(Test_Files
        ConverterJSONTests.cpp
        InvertedIndexTests.cpp
        SearchServerTests.cpp
        )

set(Src_Files
        ${MY_SRC_DIR}/ConverterJSON.cpp
        ${MY_SRC_DIR}/InvertedIndex.cpp
        ${MY_SRC_DIR}/main.cpp
        ${MY_SRC_DIR}/SearchServer.cpp
        )

set(Include_Files
        ${MY_INCLUDE_DIR}/ConverterJSON.h
        ${MY_INCLUDE_DIR}/InvertedIndex.h
        ${MY_INCLUDE_DIR}/SearchServer.h
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(SearchEngineTest ${Test_Files} ${Src_Files} ${Include_Files})

target_link_libraries(SearchEngineTest nlohmann_json::nlohmann_json GTest::gtest_main)
include(GoogleTest)
target_include_directories(SearchEngineTest PUBLIC ${MY_INCLUDE_DIR})
gtest_discover_tests(SearchEngineTest)