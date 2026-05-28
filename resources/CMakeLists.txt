file(GLOB_RECURSE RESOURCES_LIST CONFIGURE_DEPENDS "*")

foreach(RESOURCE ${RESOURCES_LIST})
    get_filename_component(FILENAME ${RESOURCE} NAME)
    if(NOT FILENAME STREQUAL "CMakeLists.txt")
        # Compute the relative path from the current source directory to the resource file
        file(RELATIVE_PATH REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${RESOURCE})
        
        # Copy to the build directory preserving the relative structure
        configure_file(${RESOURCE} ${CMAKE_BINARY_DIR}/resources/${REL_PATH} COPYONLY)
    endif()
endforeach()