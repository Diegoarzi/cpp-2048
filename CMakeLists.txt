cmake_minimum_required(VERSION 3.31)
project(cpp_2048)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_2048 main.cpp
        Game2048.cpp
        Game2048.h)
