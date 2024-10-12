cmake_minimum_required(VERSION 3.10)

# Set the project name
project(myRayTracer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(myRayTracer "../Source/main.cpp")

# Set output directories for different build types (Debug, Release)
set_target_properties(myRayTracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
)

# Enable optimization for Release builds
if (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(myRayTracer PRIVATE -O3)
endif()
