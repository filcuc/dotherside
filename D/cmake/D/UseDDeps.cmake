# Dependency tracking for D
#
#  Copyright (c) 2010 Jens Mueller <jens.k.mueller@gmx.de>
#
# All rights reserved.
#
# See LICENSE for details.
#

macro(add_executable_with_dependencies _target)
	# extract D source files from arguments
	foreach(file ${ARGV})
		if(${file} MATCHES "\\.d$")
			list(APPEND d_source_files ${file})
		endif()
	endforeach()

	#message("D files in arguments: ${d_source_files}")

	foreach(file IN LISTS d_source_files)
		set(source_file "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
		set(dependency_file "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${file}-depend.cmake")
		set(dependency_files ${dependency_files} ${dependency_file})

		#message("Checking dependencies for ${source_file}")
		#message("Put into ${dependency_file}")
		# TODO
		# better way to get the included directories
		get_directory_property(include_dirs INCLUDE_DIRECTORIES)
		set(INCLUDES )
		foreach(include_dir IN LISTS include_dirs)
			list(APPEND INCLUDES "${CMAKE_INCLUDE_FLAG_D}${include_dir}")
		endforeach()

		execute_process(
			COMMAND ${CMAKE_COMMAND}
			-D "CMAKE_D_COMPILER:STRING=${CMAKE_D_COMPILER}"
			-D "CMAKE_D_FLAGS:STRING=${CMAKE_D_FLAGS}"
			-D "include_directories:STRING=${INCLUDES}"
			-D "source_file:STRING=${source_file}"
			-D "dependency_file:STRING=${dependency_file}"
			-P "${CMAKE_ROOT}/Modules/dependencies.cmake" # TODO hard coded path
			)

		# load dependencies from file
		include(${dependency_file})
		#message("DEPENDENCIES ${D_DMD_DEPEND}")

		add_custom_command(
			OUTPUT ${dependency_file}
			DEPENDS ${D_DMD_DEPEND}
			COMMAND ${CMAKE_COMMAND}
			-D "CMAKE_D_COMPILER:STRING=${CMAKE_D_COMPILER}"
			-D "CMAKE_D_FLAGS:STRING=${CMAKE_D_FLAGS}"
			-D "include_directories:STRING=${INCLUDES}"
			-D "source_file:STRING=${source_file}"
			-D "dependency_file:STRING=${dependency_file}"
			-P "${CMAKE_ROOT}/Modules/dependencies.cmake" # TODO hard coded path
			COMMENT "Scanning for dependencies"
			)
	endforeach()

	add_executable(${ARGV} ${dependency_files})
endmacro(add_executable_with_dependencies)
