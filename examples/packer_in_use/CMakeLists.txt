pack_resources(pack_file
    JSON_FILES 
		"${PROJECT_SOURCE_DIR}/examples/data/example_data.json"
	 	"${PROJECT_SOURCE_DIR}/examples/data/example_data_part2.json" 
	OUTPUT_FILE "${PROJECT_BINARY_DIR}/my_own_pack.sqlite"
	WORKING_DIRECTORY "C:/git/personal/packer/examples/data/"
    FORCE)


add_executable(example_app main.cpp ${pack_file})
target_link_libraries(example_app packer_library)

add_custom_command(TARGET example_app POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy ${pack_file} $<TARGET_FILE_DIR:example_app>
	  COMMAND_EXPAND_LISTS
	  )
set_target_properties(example_app PROPERTIES FOLDER "Examples")


add_test(
	NAME example_app 
	COMMAND $<TARGET_FILE:example_app> 
	WORKING_DIRECTORY $<TARGET_FILE_DIR:example_app>
)