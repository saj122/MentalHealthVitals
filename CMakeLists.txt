cmake_minimum_required(VERSION 3.14)

project(DepressionRecognition)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

add_compile_definitions(CONFIG_PATH=\"${CMAKE_SOURCE_DIR}/config/camera.json\")

include(CTest)

add_subdirectory(DRUtils)
add_subdirectory(CameraController)
add_subdirectory(Viewer)
add_subdirectory(ImageProcessing)