cmake_minimum_required(VERSION 3.10)

# Name of your project
project(cmake_init)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory (optional if you separate headers)
include_directories(include)

# Add the executable
add_executable(cmake_init
    src/main.cpp
    src/utils.cpp
)
