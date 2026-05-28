cmake_minimum_required (VERSION 3.26)

project (oop1_project)
set (MY_AUTHORS "Binyamin_Mandel-yitzhak_rose")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
if (NOT MSVC)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endif()

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

include (cmake/Zip.cmake)

# 1. Force Shared Libraries (Homebrew default)
set(SFML_STATIC_LIBRARIES OFF)

# 2. Find SFML 3 components
# Graphics and Audio are required for all platforms
find_package (SFML 3.0 COMPONENTS Graphics Audio REQUIRED)

# 3. Link common libraries
target_link_libraries (${CMAKE_PROJECT_NAME} SFML::Graphics SFML::Audio)

# 4. Windows-specific configuration
if (WIN32)
    # On Windows, we need the Main component to handle the entry point correctly
    find_package (SFML 3.0 COMPONENTS Main REQUIRED)
    target_link_libraries (${CMAKE_PROJECT_NAME} SFML::Main)
endif()

include (cmake/SFML.cmake)
