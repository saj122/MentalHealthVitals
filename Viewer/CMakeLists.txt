cmake_minimum_required(VERSION 3.5)

project(Viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Core Widgets Gui OpenGL OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets Gui OpenGL OpenGLWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        ImageViewer.cpp
        ImageViewer.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/DRUtils)

target_link_libraries(${PROJECT_NAME} Qt6::Core)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} Qt6::Gui)
target_link_libraries(${PROJECT_NAME} Qt6::OpenGL)
target_link_libraries(${PROJECT_NAME} Qt6::OpenGLWidgets)
target_link_libraries(${PROJECT_NAME} DRUtils)
