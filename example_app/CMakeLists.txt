pack_resources(pack_file
    JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../example/example_data.json"
    FORCE)

add_executable(example_app main.cpp ${pack_file})

add_custom_command(TARGET example_app POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy ${pack_file} $<TARGET_FILE_DIR:example_app>
	  COMMAND_EXPAND_LISTS
	  )