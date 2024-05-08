cmake_minimum_required(VERSION 3.28...3.29)

set(PROJECT_VERSION 0.0.1)
project(packer
    VERSION ${PROJECT_VERSION}
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

configure_file("config.h.in" "${PROJECT_BINARY_DIR}/packer/private/config.h")

include(dependecies)
add_subdirectory(src)