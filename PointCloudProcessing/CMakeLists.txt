cmake_minimum_required(VERSION 3.14)

project(PointCloudProcessing LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Open3D REQUIRED)
find_package(glog REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/DRUtils)

target_link_libraries(${PROJECT_NAME} PRIVATE DRUtils)
target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
target_link_libraries(${PROJECT_NAME} PRIVATE Open3D::Open3D)