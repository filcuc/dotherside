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

SET(CMAKE_D_OUTPUT_EXTENSION .o)
SET(CMAKE_D_DASH_O "-of")
SET(CMAKE_BASE_NAME dmd)

SET(CMAKE_STATIC_LIBRARY_CREATE_D_FLAGS "-lib")

SET(CMAKE_SHARED_LIBRARY_D_FLAGS "")            # -pic
SET(CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS "-shared -defaultlib=libphobos2.so")       # -shared
SET(CMAKE_SHARED_LIBRARY_LINK_D_FLAGS "")         # +s, flag for exe link to use shared lib
SET(CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG "")       # -rpath
SET(CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG_SEP "")   # : or empty
SET(CMAKE_SHARED_LIBRARY_SONAME_D_FLAG "-L-soname=")
SET(CMAKE_SHARED_LIBRARY_RPATH_LINK_D_FLAG "-L-rpath=")
SET(CMAKE_INCLUDE_FLAG_D "-I")       # -I
SET(CMAKE_INCLUDE_FLAG_D_SEP "")     # , or empty
SET(CMAKE_LIBRARY_PATH_FLAG "-L-L")
SET(CMAKE_LIBRARY_PATH_TERMINATOR "")  # for the Digital Mars D compiler the link paths have to be terminated with a "/"
SET(CMAKE_LINK_LIBRARY_FLAG "-L-l")

SET(CMAKE_D_COMPILE_OPTIONS_PIC "-fPIC")

SET(CMAKE_LINK_LIBRARY_SUFFIX "")
SET(CMAKE_STATIC_LIBRARY_PREFIX "lib")
SET(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
SET(CMAKE_SHARED_LIBRARY_PREFIX "lib")          # lib
SET(CMAKE_SHARED_LIBRARY_SUFFIX ".so")          # .so
SET(CMAKE_EXECUTABLE_SUFFIX "")          # .exe
SET(CMAKE_DL_LIBS "dl")

SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")

#SET(CMAKE_D_STDLIBS "-L-lphobos2 -L-lpthread -L-lm -defaultlib=libphobos2.so")

#SET (CMAKE_D_FLAGS_INIT "-version=${CMAKE_BUILD_TYPE}Build ${DSTDLIB_FLAGS} ${DSTDLIB_TYPE} -I$ENV{D_PATH}/include -I$ENV{D_PATH}/import -I${CMAKE_PROJECT_SOURCE_DIR}")
SET (CMAKE_D_FLAGS_INIT "")

SET (CMAKE_D_LINK_FLAGS "")
SET (CMAKE_D_FLAGS_DEBUG_INIT "-g -debug -L--export-dynamic ${DDOC_FLAGS}")
#  SET (CMAKE_D_FLAGS_MINSIZEREL_INIT "-Os ${DDOC_FLAGS}")
SET (CMAKE_D_FLAGS_RELEASE_INIT "-O ${DDOC_FLAGS}")
SET (CMAKE_D_FLAGS_RELWITHDEBINFO_INIT "-O -g -L--export-dynamic ${DDOC_FLAGS}")
#  SET (CMAKE_D_CREATE_PREPROCESSED_SOURCE "<CMAKE_D_COMPILER> <FLAGS> -E <SOURCE> > <PREPROCESSED_SOURCE>")
SET (CMAKE_D_CREATE_ASSEMBLY_SOURCE "<CMAKE_D_COMPILER> <FLAGS> -S <SOURCE> -of<ASSEMBLY_SOURCE>")
#  SET (CMAKE_INCLUDE_SYSTEM_FLAG_D "-isystem ")
