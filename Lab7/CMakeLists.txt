cmake_minimum_required(VERSION 3.16)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Имя исполняемого файла
add_executable(MyProject
    src/main.cpp
)

# Папка с заголовочными файлами
target_include_directories(MyProject PRIVATE include)

# Полезные флаги для GCC/MinGW
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(MyProject PRIVATE -Wall -Wextra -Wpedantic)
endif()