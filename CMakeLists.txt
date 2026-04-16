include(GenerateExportHeader)

cmake_minimum_required(VERSION 3.13..4.3)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    FurredEngine
    LANGUAGES C
    VERSION 0.0.1
)

option(FE_BUILD_TESTS "Whether to build test executables" ON)

# Global Utilities

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Init project

add_library(FurredEngine)
generate_export_header(FurredEngine)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(FurredEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Configure submodules

include(glad)
include(glfw)

# Configure tests

if (FE_BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()