function(pack_resources out_var)
    set(flags FORCE)
    set(args JSON_FILE OUTPUT_FILE)
    set(listArgs)

    cmake_parse_arguments(PR_ARG "${flags}" "${args}" "${listArgs}" ${ARGN})

    if (NOT PR_ARG_JSON_FILE)
        message(FATAL_ERROR "[pack_resources]: JSON_FILE is a required argument")
    endif()

    if(${PR_ARG_FORCE})
        set(PR_ARG_FORCE "-f")
    endif()

    if(NOT PR_ARG_OUTPUT_FILE)
        set(PR_ARG_OUTPUT_FILE "${PROJECT_BINARY_DIR}/pack.db")
    endif()

    file(RELATIVE_PATH input_json_f ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/${PR_ARG_JSON_FILE}")
    set(PR_ARG_JSON_FILE "-i ${input_json_f}")
    get_filename_component(out_f_dir "${PR_ARG_OUTPUT_FILE}" DIRECTORY)
    get_filename_component(work_dir "${input_json_f}" DIRECTORY)
    add_custom_command(OUTPUT ${PR_ARG_OUTPUT_FILE}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${out_f_dir}"
            COMMAND packer ${PR_ARG_FORCE} -i "${input_json_f}" -o ${PR_ARG_OUTPUT_FILE}
            DEPENDS "${input_json_f}" packer
            WORKING_DIRECTORY ${work_dir}
            COMMENT "Packing stuff from ${input_json_f} into ${PR_ARG_OUTPUT_FILE}"
            VERBATIM)
    set(${out_var} "${PR_ARG_OUTPUT_FILE}" PARENT_SCOPE)
endfunction()