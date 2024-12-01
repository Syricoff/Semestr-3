cmake_minimum_required(VERSION 3.10)
project(AssemblyProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Пути к файлам
set(CPP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
set(ASM_OBJ ${CMAKE_CURRENT_SOURCE_DIR}/tasm_/LR6.obj)

# Проверка существования объекта
if(NOT EXISTS ${ASM_OBJ})
    message(FATAL_ERROR "Файл ${ASM_OBJ} не найден. Проверьте путь к LR6.obj.")
endif()

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${CPP_SRC})

# Добавление объектного файла через библиотеку
add_library(asm_obj STATIC IMPORTED)
set_target_properties(asm_obj PROPERTIES IMPORTED_LOCATION ${ASM_OBJ})

# Линковка с объектной библиотекой
target_link_libraries(${PROJECT_NAME} PRIVATE asm_obj)