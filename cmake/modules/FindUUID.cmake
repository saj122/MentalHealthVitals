if(CYGWIN)
    set(old_suffixes ${CMAKE_FIND_LIBRARY_SUFFIXES})
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll)
    find_library(LibUUID_LIBRARY
            NAMES cyguuid-1.dll
            )
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${old_suffixes})
else()
    find_library(UUID_LIBRARY
            NAMES uuid
            )
endif()
mark_as_advanced(UUID_LIBRARY)

find_path(UUID_INCLUDE_DIR
        NAMES uuid/uuid.h
        )
mark_as_advanced(UUID_INCLUDE_DIR)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(UUID
        FOUND_VAR UUID_FOUND
        REQUIRED_VARS UUID_LIBRARY UUID_INCLUDE_DIR
        )
set(UUID_FOUND ${UUID_FOUND})

if(UUID_FOUND)
    set(UUID_INCLUDE_DIRS ${UUID_INCLUDE_DIR})
    set(UUID_LIBRARIES ${UUID_LIBRARY})
    if(NOT TARGET UUID::UUID)
        add_library(UUID::UUID UNKNOWN IMPORTED)
        set_target_properties(UUID::UUID PROPERTIES
                IMPORTED_LOCATION "${UUID_LIBRARY}"
                INTERFACE_INCLUDE_DIRECTORIES "${UUID_INCLUDE_DIRS}"
                )
    endif()
endif()
