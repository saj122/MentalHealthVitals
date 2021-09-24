cmake_minimum_required(VERSION 3.14)

project(DepressionRecognition)

add_subdirectory(DRUtils)
add_subdirectory(CameraController)
add_subdirectory(Viewer)
add_subdirectory(ImageProcessing)

include(CTest)
add_subdirectory(test)
