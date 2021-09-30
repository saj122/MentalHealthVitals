find_path(glog_INCLUDE_DIR glog/logging.h)
message(STATUS "glog header found at: ${glog_INCLUDE_DIR}")

find_library(glog_LIB glog)
message(STATUS "libglog found at: ${glog_LIB}")

mark_as_advanced(glog_INCLUDE_DIR glog_LIB)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(glog REQUIRED_VARS
        glog_INCLUDE_DIR
        glog_LIB
        )

if(glog_FOUND AND NOT TARGET glog::glog)
    add_library(glog::glog SHARED IMPORTED)
    set_target_properties(glog::glog PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
            IMPORTED_LOCATION "${glog_LIB}"
            INTERFACE_INCLUDE_DIRECTORIES
            "${glog_INCLUDE_DIR}"
            )
endif()