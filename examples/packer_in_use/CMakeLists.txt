pack_resources(pack_file
    JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../data/example_data.json"
    FORCE)


add_executable(example_app main.cpp ${pack_file})
target_link_libraries(example_app packer_library)

add_custom_command(TARGET example_app POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy ${pack_file} $<TARGET_FILE_DIR:example_app>
	  COMMAND_EXPAND_LISTS
	  )
set_target_properties(example_app PROPERTIES FOLDER "Examples")