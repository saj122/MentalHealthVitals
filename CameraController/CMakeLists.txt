cmake_minimum_required(VERSION 3.14)

project(CameraController LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ENABLE_OPENNI2=TRUE)

find_package(glog REQUIRED)

find_package(PkgConfig)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0
                                     gstreamer-app-1.0)

link_directories(
        ${GLIB_LIBRARY_DIRS}
        ${GSTREAMER_LIBRARY_DIRS}
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "amd64")
        add_executable(${PROJECT_NAME}
          main.cpp
          Camera.h
          Controller.h
          Controller.cpp
          GSCamera.cpp
          GSCamera.h
          OpenNICamera.h
          OpenNICamera.cpp
        )
        
        target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/OpenNI2/Include)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/OpenNI2/MacOSX/lib/openni2/libOpenNI2.dylib)
    else()
        set(ENABLE_OPENNI2 FALSE)
        add_executable(${PROJECT_NAME}
          main.cpp
          Camera.h
          Controller.h
          Controller.cpp
          GSCamera.cpp
          GSCamera.h
        )
    endif()
elseif(UNIX)
    add_executable(${PROJECT_NAME}
          main.cpp
          Camera.h
          Controller.h
          Controller.cpp
          GSCamera.cpp
          GSCamera.h
          OpenNICamera.h
          OpenNICamera.cpp
    )
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/OpenNI2/Include)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/OpenNI2/Linux/Redist/libOpenNI2.so)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/DRUtils)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${GSTREAMER_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE DRUtils)
target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GSTREAMER_LIBRARIES})

add_dependencies(${PROJECT_NAME} DRUtils)
