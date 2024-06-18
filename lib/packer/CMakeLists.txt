set(LIBRARY_NAME
    packer_library
)

add_library(${LIBRARY_NAME}
    src/Packer.cpp    
    ${PACKER_LIBRARY_INCLUDE_DIR}/packer/Packer.hpp
    ${PACKER_LIBRARY_INCLUDE_DIR}/packer/LogEntry.hpp    
)

target_link_libraries(${LIBRARY_NAME} SQLiteCpp sqlite3)

target_include_directories(${LIBRARY_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}/include
    $<BUILD_INTERFACE:${PACKER_LIBRARY_INCLUDE_DIR}/${LIBRARY_NAME}>    
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${PACKER_LIBRARY_INCLUDE_DIR}>    
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
                        PROJECT_LABEL "Packer Library"                        
                        OUTPUT_NAME "packer")