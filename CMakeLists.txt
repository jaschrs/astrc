cmake_minimum_required(VERSION 4.2)
project(StaticTrace)

set(CMAKE_CXX_STANDARD 26)

add_executable(StaticTrace src/main.cpp
        include/ConfigParser.h)
