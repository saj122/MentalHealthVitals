cmake_minimum_required(VERSION 3.14)

project(DepressionRecognition)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

add_compile_definitions(CONFIG_PATH=\"${CMAKE_SOURCE_DIR}/config/camera.json\")
add_compile_definitions(HAARCASCADE_PATH=\"${CMAKE_SOURCE_DIR}/ImageProcessing/models/haarcascade_frontalface_default.xml\")
add_compile_definitions(EMOTION_MODEL_PATH=\"${CMAKE_SOURCE_DIR}/ImageProcessing/models/model.h5\")

include(CTest)

add_subdirectory(DRUtils)
add_subdirectory(CameraController)
add_subdirectory(Viewer)
add_subdirectory(ImageProcessing)