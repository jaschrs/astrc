cmake_minimum_required(VERSION 4.2)
project(StaticTrace)

set(CMAKE_CXX_STANDARD 26)

add_executable(StaticTrace src/main.cpp
        include/ConfigParser.hpp
        include/AssetMapper.hpp
        include/CodeScanner.hpp
        include/ReportGenerator.hpp
        src/ConfigParser.cpp
        src/AssetMapper.cpp
        src/CodeScanner.cpp
        src/ReportGenerator.cpp)
