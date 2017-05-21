cmake_minimum_required(VERSION 3.7)
project(a3search)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp a2search.cpp)
add_executable(a3search ${SOURCE_FILES})