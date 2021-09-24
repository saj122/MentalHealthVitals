cmake_minimum_required(VERSION 3.14)

project(DRUtils LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  glog
  URL https://github.com/google/glog/archive/8f9ccfe770add9e4c64e9b25c102658e3c763b73.zip
)

set(glog_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glog)

add_library(${PROJECT_NAME} STATIC
  Memory.cpp
  Memory.h
)

target_link_libraries(${PROJECT_NAME} glog::glog)
