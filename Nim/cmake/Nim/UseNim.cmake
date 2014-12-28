include(CMakeParseArguments)

function(add_nim_executable )
    cmake_parse_arguments(ARGS "" "TARGET" "SOURCES" ${ARGN})

    # collect set of input source files
    set(in_files "")
    foreach(src ${ARGS_SOURCES} ${ARGS_UNPARSED_ARGUMENTS})
        list(APPEND in_files "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
    endforeach(src ${ARGS_SOURCES} ${ARGS_UNPARSED_ARGUMENTS})

    # set the target binary and nim cache directory
    set(nim_target "${CMAKE_CURRENT_BINARY_DIR}/${ARGS_TARGET}")
    set(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/nimcache")

    # add target to trigger the nimrod compiler
    add_custom_target(
    	nim ALL
    	COMMAND
        	${NIM_EXECUTABLE} "c" "--nimcache:" ${DIRECTORY} "--out:" ${nim_target} ${in_files}
    	DEPENDS
        	${in_files}
    )
endfunction(add_nim_executable)