include(CMakeParseArguments)

function(add_nim_executable )
  set(options )
  set(oneValueArgs TARGET)
  set(multiValueArgs SOURCES PATHS)
  cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  
  # collect set of input source files
  set(in_files "")
  foreach(src ${ARGS_SOURCES} ${ARGS_UNPARSED_ARGUMENTS})
    list(APPEND in_files "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
  endforeach(src ${ARGS_SOURCES} ${ARGS_UNPARSED_ARGUMENTS})

  set(in_paths "")
  foreach(path ${ARGS_PATHS} ${ARGS_UNPARSED_ARGUMENTS})
    list(APPEND in_paths "--path:${CMAKE_CURRENT_SOURCE_DIR}/${path}")
  endforeach(path ${ARGS_PATHS} ${ARGS_UNPARSED_ARGUMENTS})
  
  # set the target binary and nim cache directory
  set(nim_target "${CMAKE_CURRENT_BINARY_DIR}/${ARGS_TARGET}")
  set(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/nimcache")

  # add target to trigger the nimrod compiler
  add_custom_target(
      ${ARGS_TARGET} ALL
      COMMAND
	      ${NIM_EXECUTABLE} "cpp" ${in_paths} "--nimcache:" ${DIRECTORY} "--out:" ${nim_target} ${in_files} 
      DEPENDS
	      ${in_files}
  )
endfunction(add_nim_executable)