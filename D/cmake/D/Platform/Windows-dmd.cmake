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

#SET(DSTDLIB_FLAGS "-version=Phobos")
IF(CMAKE_D_BUILD_DOCS)
	SET(DDOC_FLAGS "-D -Dddocumentation")
	#FOREACH(item ${CMAKE_D_DDOC_FILES})
	#	SET(DDOC_FLAGS "${DDOC_FLAGS} ${item}")
	#ENDFOREACH(item)
ENDIF(CMAKE_D_BUILD_DOCS)

SET(CMAKE_D_OUTPUT_EXTENSION .obj)
SET(CMAKE_D_DASH_O "-of")
SET(CMAKE_BASE_NAME dmd)

SET(CMAKE_STATIC_LIBRARY_CREATE_D_FLAGS "-lib")

SET(CMAKE_SHARED_LIBRARY_D_FLAGS "")            # -pic
SET(CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS "-shared")       # -shared
SET(CMAKE_SHARED_LIBRARY_LINK_D_FLAGS "")         # +s, flag for exe link to use shared lib
SET(CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG "")       # -rpath
SET(CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG_SEP "")   # : or empty
SET(CMAKE_INCLUDE_FLAG_D "-I")       # -I
SET(CMAKE_INCLUDE_FLAG_D_SEP "")     # , or empty
SET(CMAKE_LIBRARY_PATH_FLAG "-L-L")
SET(CMAKE_LIBRARY_PATH_TERMINATOR "")  # for the Digital Mars D compiler the link paths have to be terminated with a "/"

SET(CMAKE_LINK_LIBRARY_FLAG "-L-l")
SET(CMAKE_STATIC_LIBRARY_PREFIX "")				#
SET(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")			# lib
SET(CMAKE_SHARED_LIBRARY_PREFIX "")          	#
SET(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")         # .dll
SET(CMAKE_EXECUTABLE_SUFFIX ".exe")          	# .exe
SET(CMAKE_DL_LIBS "dl")

SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")

SET (CMAKE_D_FLAGS_INIT "")
# DMD can only produce 32-bit binaries for now
SET (CMAKE_D_LINK_FLAGS "")
SET (CMAKE_D_FLAGS_DEBUG_INIT "-g -debug ${DDOC_FLAGS}")
SET (CMAKE_D_FLAGS_RELEASE_INIT "-O -release -inline ${DDOC_FLAGS}")
SET (CMAKE_D_FLAGS_RELWITHDEBINFO_INIT "-O -g ${DDOC_FLAGS}")
SET (CMAKE_D_CREATE_ASSEMBLY_SOURCE "<CMAKE_D_COMPILER> <FLAGS> -S <SOURCE> -of<ASSEMBLY_SOURCE>")
