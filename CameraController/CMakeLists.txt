cmake_minimum_required(VERSION 3.14)

project(CameraController LANGUAGES CXX)

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

add_executable(${PROJECT_NAME}
  main.cpp
  Camera.h
  Controller.h
  Controller.cpp
  OpenNICamera.h
  OpenNICamera.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/OpenNI2/Include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/DRUtils)

target_link_libraries(${PROJECT_NAME} DRUtils)
target_link_libraries(${PROJECT_NAME} glog::glog)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/OpenNI2/Windows/Lib/OpenNI2.lib)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/OpenNI2/Linux/Redist/libOpenNI2.so)
endif()

add_dependencies(${PROJECT_NAME} DRUtils)
