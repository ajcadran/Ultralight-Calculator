project(Calculator C CXX)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

set(SOURCES "src/Calculator.h"
            "src/Calculator.cpp"
            "src/main.cpp"
            "src/Math.h"
            "src/Math.cpp")

add_app("${SOURCES}")