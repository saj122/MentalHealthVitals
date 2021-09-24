cmake_minimum_required(VERSION 3.14)

project(DRUtils LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  glog
  GIT_REPOSITORY https://github.com/google/glog.git
  CMAKE_ARGS -DBUILD_TESTING=OFF
)

FetchContent_MakeAvailable(glog)

add_library(${PROJECT_NAME} STATIC
  Memory.cpp
  Memory.h
)

target_link_libraries(${PROJECT_NAME} glog::glog)
