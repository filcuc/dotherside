# This modules add functions for downloading and building dub dependencies.
# This code sets the following variables and functions:
#
# DUB_DIRECTORY = the full path to Dub pacakges
#
# DubProject_Add(<dub_package> [version]) 
#
#============================================================================
#  Copyright (c) 2014 Dragos Carp <dragos.carp@gmail.com>
#
# All rights reserved.
#
# See LICENSE for details.
#

if(NOT DUB_DIRECTORY)
	set(DUB_DIRECTORY ${CMAKE_BINARY_DIR}/UseDub CACHE PATH "Dub packages directory")
endif(NOT DUB_DIRECTORY)

set(DUB_REGISTRY "http://code.dlang.org/packages")
file(MAKE_DIRECTORY ${DUB_DIRECTORY}/CMakeTmp)

if(NOT CMAKE_D_COMPILER)
	message(FATAL_ERROR "UseDub needs a D compiler or use it in a D project.")
endif(NOT CMAKE_D_COMPILER)

#compile json parsers
if(NOT EXISTS ${DUB_DIRECTORY}/CMakeTmp/DubUrl)
	find_file(DUB_GET_PACKAGE_URL_D_SRC "DubUrl.d"
		PATHS ${CMAKE_ROOT}/Modules ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH
		PATH_SUFFIXES "UseDub")
	find_file(SEMVER_SRC "semver.d"
		PATHS ${CMAKE_ROOT}/Modules ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH
		PATH_SUFFIXES "UseDub")
	get_filename_component(SEMVER_PATH ${SEMVER_SRC} PATH)
	execute_process(COMMAND ${CMAKE_D_COMPILER} -I${SEMVER_PATH} ${DUB_GET_PACKAGE_URL_D_SRC} ${SEMVER_SRC}
		WORKING_DIRECTORY ${DUB_DIRECTORY}/CMakeTmp)
	unset(DUB_GET_PACKAGE_URL_D_SRC CACHE)
endif(NOT EXISTS ${DUB_DIRECTORY}/CMakeTmp/DubUrl)
if(NOT EXISTS ${DUB_DIRECTORY}/CMakeTmp/DubToCMake)
	find_file(DUB_PACKAGE_TO_CMAKE_D_SRC "DubToCMake.d"
		PATHS ${CMAKE_ROOT}/Modules ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH
		PATH_SUFFIXES "UseDub")
	execute_process(COMMAND ${CMAKE_D_COMPILER} ${DUB_PACKAGE_TO_CMAKE_D_SRC}
		WORKING_DIRECTORY ${DUB_DIRECTORY}/CMakeTmp)
	unset(DUB_PACKAGE_TO_CMAKE_D_SRC CACHE)
endif(NOT EXISTS ${DUB_DIRECTORY}/CMakeTmp/DubToCMake)

include(ExternalProject)

function(DubProject_Add name)
	if(NOT EXISTS ${DUB_DIRECTORY}/${name}.json)
		file(DOWNLOAD ${DUB_REGISTRY}/${name}.json ${DUB_DIRECTORY}/${name}.json STATUS status)
		list(GET status 0 statusCode)
		
		if(NOT statusCode EQUAL 0)
			file(REMOVE ${DUB_DIRECTORY}/${name}.json)
			message(FATAL_ERROR "Failed to download ${DUB_REGISTRY}/${name}.json")
		endif(NOT statusCode EQUAL 0)
	endif(NOT EXISTS ${DUB_DIRECTORY}/${name}.json)

	if(${ARGC} GREATER 1)
		execute_process(COMMAND ${DUB_DIRECTORY}/CMakeTmp/DubUrl -p ${name}.json -t ${ARGN}
			WORKING_DIRECTORY ${DUB_DIRECTORY})
	else(${ARGC} GREATER 1)
		execute_process(COMMAND ${DUB_DIRECTORY}/CMakeTmp/DubUrl -p ${name}.json
			WORKING_DIRECTORY ${DUB_DIRECTORY})
	endif(${ARGC} GREATER 1)

	include(${DUB_DIRECTORY}/${name}.cmake)

	ExternalProject_Add(${name}
		DOWNLOAD_DIR ${DUB_DIRECTORY}/archive/${name}
		SOURCE_DIR ${DUB_DIRECTORY}/source/${name}
		URL ${DUB_PACKAGE_URL}
		PATCH_COMMAND ${DUB_DIRECTORY}/CMakeTmp/DubToCMake -p package.json
		INSTALL_DIR ${DUB_DIRECTORY}/export
		CMAKE_CACHE_ARGS
			-DCMAKE_MODULE_PATH:PATH=${CMAKE_MODULE_PATH}
			-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			-DDUB_DIRECTORY:PATH=${DUB_DIRECTORY})

	include_directories(${DUB_DIRECTORY}/source/${name}/source ${DUB_DIRECTORY}/source/${name}/src)
endfunction()
