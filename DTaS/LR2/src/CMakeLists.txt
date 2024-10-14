cmake_minimum_required(VERSION 3.10)

project(LR2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    BinTree.cpp
    CMenu.cpp
    CMenuItem.cpp
    MyError.cpp
    Tools.cpp
)

add_executable(LR2 ${SOURCES})

