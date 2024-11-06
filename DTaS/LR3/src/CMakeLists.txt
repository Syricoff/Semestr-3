cmake_minimum_required(VERSION 3.10)

project(LR3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    Graph.cpp
)

add_executable(LR3 ${SOURCES})

