
if (WIN32)
    # During build, copy the Slang DLLs to the output directories
    # If not done, this will result in runtime errors when trying to load the DLLs
    file(COPY "${CMAKE_SOURCE_DIR}/vendor/slang/win_x64/"
            DESTINATION "${CMAKE_BINARY_DIR}/Debug")

    file(COPY "${CMAKE_SOURCE_DIR}/vendor/slang/win_x64/"
            DESTINATION "${CMAKE_BINARY_DIR}/Release")
endif ()

if(APPLE)
    # During build, copy the Slang dylibs to the output directories
    # If not done, this will result in runtime errors when trying to load the dylibs
    file(COPY "${CMAKE_SOURCE_DIR}/vendor/slang/macos/"
            DESTINATION "${CMAKE_BINARY_DIR}/Debug")

    file(COPY "${CMAKE_SOURCE_DIR}/vendor/slang/macos/"
            DESTINATION "${CMAKE_BINARY_DIR}/Release")
endif()