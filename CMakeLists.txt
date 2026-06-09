cmake_minimum_required(VERSION 3.20)
project(astrc)

set(CMAKE_CXX_STANDARD 26)

add_executable(astrc src/main.cpp
        include/Parser.hpp
        include/Mapper.hpp
        include/Scanner.hpp
        src/Parser.cpp
        src/Mapper.cpp
        src/Scanner.cpp
)

target_compile_options(astrc PRIVATE "-O1")