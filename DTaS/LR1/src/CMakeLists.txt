cmake_minimum_required(VERSION 3.10)
project(DoubleListApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Укажите все исходные файлы вашего проекта
set(SOURCES
    main.cpp
    CMenu.cpp
    CMenuItem.cpp
    DoubleList.cpp
    FileLogging.cpp
    MyError.cpp
)

# Создайте исполняемый файл из указанных исходных файлов
add_executable(DoubleListApp ${SOURCES})
