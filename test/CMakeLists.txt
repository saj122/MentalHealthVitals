cmake_minimum_required(VERSION 3.14)

project(Test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets Gui OpenGL OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets Gui OpenGL OpenGLWidgets REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  CMAKE_ARGS -DBUILD_TESTING=OFF
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  glog
  GIT_REPOSITORY https://github.com/google/glog.git
  CMAKE_ARGS -DBUILD_TESTING=OFF
)

FetchContent_MakeAvailable(glog)

add_executable(
  ${PROJECT_NAME}
  CameraControllerTest.cpp
  DRUtilsTest.cpp
  ViewerTest.cpp
  ImageProcessingTest.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  gtest_main
  ${CMAKE_BINARY_DIR}/CameraController/CMakeFiles/CameraController.dir/OpenNICamera.cpp.o
  glog::glog
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} Qt6::Core)
target_link_libraries(${PROJECT_NAME} Qt6::Gui)
target_link_libraries(${PROJECT_NAME} Qt6::OpenGL)
target_link_libraries(${PROJECT_NAME} Qt6::OpenGLWidgets)
target_link_libraries(${PROJECT_NAME} DRUtils)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/DRUtils)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/CameraController)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Viewer)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/OpenNI2/Include)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/OpenNI2/Windows/Lib/OpenNI2.lib)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/OpenNI2/Linux/Redist/libOpenNI2.so)
endif()
