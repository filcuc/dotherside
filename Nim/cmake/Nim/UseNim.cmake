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
  set(nim_cache_dir "${CMAKE_CURRENT_BINARY_DIR}/nimcache")

  # compiler 
  set(nim_compiler "c")
  
  # compiler options
  set(nim_compiler_options "")
  if (WIN32)
    if (MSVC OR MSVC_IDE)
	  set(nim_compiler_options "--cc:vcc")
	endif()
  endif()
  
  # thread options
  set(nim_thread_options "")
  if(UNIX)
    set(nim_thread_options "--passL:-lpthread")
  endif()

  # add target to trigger the nimrod compiler
  add_custom_target(
      ${ARGS_TARGET} ALL
      COMMAND
	      ${NIM_EXECUTABLE} ${nim_compiler} ${nim_compiler_options} ${nim_thread_options} ${in_paths} "--nimcache:" ${nim_cache_dir} "--out:" ${nim_target} ${in_files}
      DEPENDS
	      ${in_files}
  )
endfunction(add_nim_executable)