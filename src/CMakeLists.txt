set(EMBEDED_FILES 
    "sql/create_file_table.sql"
    "sql/create_store_table.sql"
    "sql/create_translation_table.sql"
    "sql/insert_key_value.sql"
    "sql/insert_file.sql"
    "sql/insert_translation.sql"
)
add_custom_target(packer_resources SOURCES ${EMBEDED_FILES})
source_group("Embeded Files" REGULAR_EXPRESSION ".*sql.hpp$")
embed_resources(LIBRARY_RESOURCES_HPP CONTENT_AS_COMMENT FILES ${EMBEDED_FILES} )

add_executable(packer 
    main.cpp    
    Packer.cpp
    Packer.h
    PackerArgument.h
    PackerArgument.cpp

    sources/PackSource.h
    sources/JsonPackSource.h
    sources/JsonPackSource.cpp

    sinks/PackSink.h
    sinks/SqlitePackSink.h
    sinks/SqlitePackSink.cpp   
    
    packTypes/PackTypes.h
    packTypes/KeyValuePackType.hpp
    packTypes/FilePackType.hpp
    packTypes/TranslationPackType.hpp

    utils/json.hpp 
    utils/Utils.cpp
    utils/Utils.h
    utils/Flags.hpp 
    utils/getopt.cpp 
    utils/getopt.h
    utils/glob.hpp 
    )
target_link_libraries(packer SQLiteCpp sqlite3)
target_include_directories(packer PRIVATE "${PROJECT_BINARY_DIR}/include" ${PROJECT_BINARY_DIR} SQLiteCpp sqlite3)
set_target_properties(packer PROPERTIES
    PROJECT_LABEL "Packer Application"                        
    OUTPUT_NAME "packer"
    VS_DEBUGGER_COMMAND_ARGUMENTS "-f -i ${CMAKE_SOURCE_DIR}/examples/data/example_data.json -o ${CMAKE_BINARY_DIR}/res.db"
    VS_DEBUGGER_WORKING_DIRECTORY "C:/git/personal/sqlite_packer/examples/data" )