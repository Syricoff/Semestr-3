cmake_minimum_required(VERSION 3.10)

project(LR4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    ProfileMatrix.cpp
)

add_executable(LR4 ${SOURCES})

