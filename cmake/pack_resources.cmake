function(pack_resources out_var)
    set(flags FORCE)
    set(args OUTPUT_FILE WORKING_DIRECTORY)
    set(listArgs JSON_FILES)

    cmake_parse_arguments(PR_ARG "${flags}" "${args}" "${listArgs}" ${ARGN})

    if (NOT PR_ARG_JSON_FILES)
        message(FATAL_ERROR "[pack_resources]: JSON_FILES is a required argument")
    endif()

    if(${PR_ARG_FORCE})
        set(PR_ARG_FORCE "-f")
    endif()

    if(NOT PR_ARG_OUTPUT_FILE)
        set(PR_ARG_OUTPUT_FILE "${PROJECT_BINARY_DIR}/pack.db")
    endif()

    get_filename_component(out_f_dir "${PR_ARG_OUTPUT_FILE}" DIRECTORY)
    list(JOIN PR_ARG_JSON_FILES " " PACKER_FILES)
    add_custom_command(OUTPUT ${PR_ARG_OUTPUT_FILE}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${out_f_dir}"
            COMMAND packer ${PR_ARG_FORCE} -o ${PR_ARG_OUTPUT_FILE} -- ${PR_ARG_JSON_FILES}
            DEPENDS ${PR_ARG_JSON_FILES} packer
            WORKING_DIRECTORY ${PR_ARG_WORKING_DIRECTORY}
            COMMENT "Packing stuff from ${PR_ARG_JSON_FILES} into ${PR_ARG_OUTPUT_FILE}"
            VERBATIM)
    set(${out_var} "${PR_ARG_OUTPUT_FILE}" PARENT_SCOPE)
endfunction()