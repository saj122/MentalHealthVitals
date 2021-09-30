cmake_minimum_required(VERSION 3.14)

project(DRUtils LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glog REQUIRED)

if(WIN32)
    add_library(${PROJECT_NAME} STATIC
            Memory.h
            MemoryWindows.cpp
            MemoryWindows.h
            MemoryFactory.h
    )
elseif(UNIX)
    add_library(${PROJECT_NAME} STATIC
            MemoryLinux.cpp
            MemoryLinux.h
            Memory.h
            MemoryFactory.h
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)

enable_testing()

include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(DRUtilsTest MemoryTest.cpp)

target_link_libraries(DRUtilsTest
                      GTest::Main
                      DRUtils)

gtest_discover_tests(DRUtilsTest)

