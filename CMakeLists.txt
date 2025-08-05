cmake_minimum_required(VERSION 3.31)
project(Wordle_Bot LANGUAGES C)

file(GLOB_RECURSE SOURCE_FILES "src/*.c" "src/*.h")
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall ")
include_directories("include")
add_executable(Wordle_Bot ${SOURCE_FILES})
