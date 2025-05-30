cmake_minimum_required(VERSION 3.10)
project(KURSACH)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(KURSACH
    src/Main.cpp
    src/railway_system.cpp
    src/sorting_node.cpp
    src/wagon.cpp
)