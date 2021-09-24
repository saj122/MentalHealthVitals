cmake_minimum_required(VERSION 3.14)

project(ImageProcessing LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS=-fuse-ld=gold)

include(FetchContent)
FetchContent_Declare(
  glog
  URL https://github.com/google/glog/archive/8f9ccfe770add9e4c64e9b25c102658e3c763b73.zip
)

set(glog_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glog)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/DRUtils)
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/tf/include)

target_link_libraries(${PROJECT_NAME} DRUtils)
target_link_libraries(${PROJECT_NAME} glog::glog)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/tf/lib/libtensorflow.so)
