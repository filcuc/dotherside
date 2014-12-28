#
# CMakeD - CMake module for D Language
#
# Copyright (c) 2007, Selman Ulug <selman.ulug@gmail.com>
#                     Tim Burrell <tim.burrell@gmail.com>
#
# All rights reserved.
#
# See LICENSE for details.
#
# Modified from CMake 2.6.5 gcc.cmake
# See http://www.cmake.org/HTML/Copyright.html for details
#

SET(CMAKE_D_DASH_O "-o")
SET(CMAKE_BASE_NAME gdc)

IF(CMAKE_D_USE_TANGO)
	SET(DSTDLIB_FLAGS "-fversion=Tango")
ENDIF(CMAKE_D_USE_TANGO)
IF(CMAKE_D_USE_PHOBOS)
	SET(DSTDLIB_FLAGS "-fversion=Phobos")
ENDIF(CMAKE_D_USE_PHOBOS)
IF(CMAKE_D_BUILD_DOCS)
	SET(DDOC_FLAGS "-fdoc -fdoc-dir=documentation")
	FOREACH(item ${CMAKE_D_DDOC_FILES})
		SET(DDOC_FLAGS "${DDOC_FLAGS} -fdoc-inc=${item}")
	ENDFOREACH(item)
ENDIF(CMAKE_D_BUILD_DOCS)

#SET (CMAKE_D_FLAGS_INIT "-fversion=Posix -fversion=${CMAKE_BUILD_TYPE}Build ${DSTDLIB_FLAGS}")
SET (CMAKE_D_FLAGS_INIT "")
SET (CMAKE_D_FLAGS_DEBUG_INIT "-g ${DDOC_FLAGS}")
SET (CMAKE_D_FLAGS_MINSIZEREL_INIT "-Os ${DDOC_FLAGS}")
SET (CMAKE_D_FLAGS_RELEASE_INIT "-O3 -fomit-frame-pointer -fweb -frelease -finline-functions ${DDOC_FLAGS}")
SET (CMAKE_D_FLAGS_RELWITHDEBINFO_INIT "-O2 -g ${DDOC_FLAGS}")
#  SET (CMAKE_D_CREATE_PREPROCESSED_SOURCE "<CMAKE_D_COMPILER> <FLAGS> -E <SOURCE> > <PREPROCESSED_SOURCE>")
SET (CMAKE_D_CREATE_ASSEMBLY_SOURCE "<CMAKE_D_COMPILER> <FLAGS> -S <SOURCE> -o <ASSEMBLY_SOURCE>")
#SET (CMAKE_INCLUDE_SYSTEM_FLAG_D "-isystem ")

SET(CMAKE_INCLUDE_FLAG_D "-I")       # -I
