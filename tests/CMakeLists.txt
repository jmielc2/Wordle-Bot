set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
project(Wordle_Tests)
add_subdirectory(googletest-1.17.0 ../include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB_RECURSE TEST_FILES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
add_executable(Wordle_Tests_tests WordBankTests.cpp)
target_link_libraries(Wordle_Tests_tests gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(Wordle_Tests_tests)
