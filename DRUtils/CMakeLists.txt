cmake_minimum_required(VERSION 3.14)

project(DRUtils LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} STATIC
  Memory.cpp
  Memory.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)
