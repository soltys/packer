
add_executable(packer 
    main.cpp    
    Packer.cpp
    ${PROJECT_INCLUDE_DIR}/packer/Packer.hpp
    ${PROJECT_INCLUDE_DIR}/packer/PackerArgument.hpp
    PackerArgument.cpp

    ${PROJECT_INCLUDE_DIR}/packer/Factory.hpp
    Factory.cpp

    ${PROJECT_INCLUDE_DIR}/packer/sources/PackSource.hpp
    ${PROJECT_INCLUDE_DIR}/packer/sources/JsonPackSource.hpp
    sources/JsonPackSource.cpp
    ${PROJECT_INCLUDE_DIR}/packer/sources/HttpPackSource.hpp
    sources/HttpPackSource.cpp

    ${PROJECT_INCLUDE_DIR}/packer/sinks/PackSink.hpp
    ${PROJECT_INCLUDE_DIR}/packer/sinks/SqlitePackSink.hpp
    sinks/SqlitePackSink.cpp   
    
    ${PROJECT_INCLUDE_DIR}/packer/pack_types/PackTypes.hpp
    ${PROJECT_INCLUDE_DIR}/packer/pack_types/KeyValuePackType.hpp
    ${PROJECT_INCLUDE_DIR}/packer/pack_types/FilePackType.hpp
    ${PROJECT_INCLUDE_DIR}/packer/pack_types/TranslationPackType.hpp
    
    ${PROJECT_INCLUDE_DIR}/packer/Utils.hpp
    Utils.cpp

    # include single header files
    ${PROJECT_INCLUDE_DIR}/nlohmann/json.hpp 
    ${PROJECT_INCLUDE_DIR}/glob/glob.hpp 
    ${PROJECT_INCLUDE_DIR}/args/args.hxx
    )
target_link_libraries(packer SQLiteCpp sqlite3)
target_include_directories(packer PRIVATE "${PROJECT_BINARY_DIR}/include" ${PROJECT_INCLUDE_DIR} SQLiteCpp sqlite3)
set_target_properties(packer PROPERTIES
    PROJECT_LABEL "Packer Application"                        
    OUTPUT_NAME "packer"
    VS_DEBUGGER_COMMAND_ARGUMENTS "-f -i ${CMAKE_SOURCE_DIR}/examples/data/example_data.json -o ${CMAKE_BINARY_DIR}/res.db"
    VS_DEBUGGER_WORKING_DIRECTORY "C:/git/personal/sqlite_packer/examples/data" )