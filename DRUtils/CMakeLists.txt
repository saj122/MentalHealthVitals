cmake_minimum_required(VERSION 3.14)

project(DRUtils LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glog REQUIRED)
find_package(RapidJSON REQUIRED)
find_package (SQLite3)
find_package(OpenSSL REQUIRED)
find_package(UUID REQUIRED)

add_library(${PROJECT_NAME} STATIC
        MemoryUnix.cpp
        MemoryUnix.h
        Memory.h
        MemoryFactory.h
        Config.h
        Database.cpp
        Database.h
        Hashing.cpp
        Hashing.h
        Patient.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${RAPIDJSON_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)
target_link_libraries(${PROJECT_NAME} PRIVATE UUID::UUID)

enable_testing()

include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(DRUtilsTest MemoryTest.cpp)

target_link_libraries(DRUtilsTest
                      GTest::Main
                      DRUtils)

gtest_discover_tests(DRUtilsTest)

