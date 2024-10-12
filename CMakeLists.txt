cmake_minimum_required(VERSION 3.10)

# Sets the project name
project(myRayTracer)

# Sets the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Creates a custom target to ensure the "Renders" folder exists
add_custom_target(create_renders_folder
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/Renders)


# Adds the executable
add_executable(myRayTracer "../Source/main.cpp")

# Sets output directories for different build types (Debug, Release)
set_target_properties(myRayTracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
)

# Makes sure this custom target runs before the executable
add_dependencies(myRayTracer create_renders_folder)

# Enables optimization for Release builds
if (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(myRayTracer PRIVATE -O3)
endif()
