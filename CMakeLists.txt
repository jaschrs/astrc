cmake_minimum_required(VERSION 4.2)
project(StaticTrace)

set(CMAKE_CXX_STANDARD 26)

add_executable(StaticTrace src/main.cpp
        include/Parser.hpp
        include/Mapper.hpp
        include/Scanner.hpp
        src/Parser.cpp
        src/Mapper.cpp
        src/Scanner.cpp
)

target_compile_options(StaticTrace PRIVATE "-O1")