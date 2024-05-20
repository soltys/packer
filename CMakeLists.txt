cmake_minimum_required(VERSION 3.28...3.29)

project(packer
    DESCRIPTION "application which puts stuff into things"
    HOMEPAGE_URL "https://github.com/soltys/packer"
    VERSION 0.0.1
    LANGUAGES CXX)

source_group("Embeded Files" REGULAR_EXPRESSION ".*sql.hpp$")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS Off )

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
configure_file("config.h.in" "${PROJECT_BINARY_DIR}/include/packer/private/config.h")

include(dependecies)

add_subdirectory(lib)
add_subdirectory(src)

include(pack_resources)

option(PACKER_BUILD_EXAMPLES "packer build examples." OFF)
if (PACKER_BUILD_EXAMPLES)
    add_subdirectory(examples)
else (PACKER_BUILD_EXAMPLES)
    message(STATUS "SQLITECPP_BUILD_EXAMPLES OFF")
endif (PACKER_BUILD_EXAMPLES)

include(get_all_targets)
get_all_targets(all_targets)

set_target_properties(${all_targets}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin"    
)

configure_file("${PROJECT_SOURCE_DIR}/.vscode/launch.json.in" "${PROJECT_SOURCE_DIR}/.vscode/launch.json")
configure_file("${PROJECT_SOURCE_DIR}/.vs/launch.vs.json.in" "${PROJECT_SOURCE_DIR}/.vs/launch.vs.json")