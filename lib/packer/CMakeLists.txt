set(LIBRARY_NAME
    packer_library
)


set(EMBEDED_FILES 
    "sql/insert_log.sql"
    "sql/get_key.sql"
    "sql/get_file.sql"
    "sql/get_toggle.sql"
    "sql/get_translation.sql"
    "sql/get_latest_logs.sql"
)
add_custom_target(packer_library_resources SOURCES ${EMBEDED_FILES})
embed_resources(PACKER_LIBRARY_RESOURCES_HPP CONTENT_AS_COMMENT FILES ${EMBEDED_FILES} )

add_library(${LIBRARY_NAME}
    src/Packer.cpp    
    include/packer/Packer.h
    include/packer/LogEntry.hpp
    ${PACKER_LIBRARY_RESOURCES_HPP}
)

target_link_libraries(${LIBRARY_NAME} SQLiteCpp sqlite3)

target_include_directories(${LIBRARY_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}/include
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>    
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>    
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
                        PROJECT_LABEL "Packer Library"                        
                        OUTPUT_NAME "packer")