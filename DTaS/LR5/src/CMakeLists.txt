cmake_minimum_required(VERSION 3.10)

project(BMP)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(bmp_editor main.cpp BMP/BMP.cpp FileLogging/FileLogging.cpp)

include_directories(BMP FileLogging)
