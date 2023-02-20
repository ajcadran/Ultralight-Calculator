project(Calculator C CXX)
cmake_minimum_required(VERSION 3.3.2)

include(cmake/App.cmake)

set(SOURCES "src/Calculator.h"
            "src/Calculator.cpp"
            "src/main.cpp"
            "src/MathHandler.h"
            "src/MathHandler.cpp"
            "src/AppHelper.h"
            "src/AppHelper.cpp")

add_app("${SOURCES}")