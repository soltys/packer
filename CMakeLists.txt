cmake_minimum_required(VERSION 3.28...3.29)

set(PROJECT_VERSION 0.0.1)
project(packer
    DESCRIPTION "application which puts stuff into things"
    HOMEPAGE_URL "https://github.com/soltys/packer"
    VERSION ${PROJECT_VERSION}
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

configure_file("config.h.in" "${PROJECT_BINARY_DIR}/packer/private/config.h")

include(dependecies)
add_subdirectory(src)

include(pack_resources)
add_subdirectory(example_app)
