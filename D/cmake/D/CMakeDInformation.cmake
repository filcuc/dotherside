#
# CMakeD - CMake module for D Language
#
# Copyright (c) 2013, Selman Ulug <selman.ulug@gmail.com>
#                     Tim Burrell <tim.burrell@gmail.com>
#                     Steve King <sk@metrokings.com>
#                     Dragos Carp <dragos.carp@gmail.com>
#                     Konstantin Oblaukhov <oblaukhov.konstantin@gmail.com>
#
# All rights reserved.
#
# See LICENSE for details.
#
# Modified from CMake 2.6.5 CMakeCInformation.cmake
# See http://www.cmake.org/HTML/Copyright.html for details
#

# This file sets the basic flags for the D language in CMake.
# It also loads the available platform file for the system-compiler
# if it exists.
# It also loads a system - compiler - processor (or target hardware)
# specific file, which is mainly useful for crosscompiling and embedded systems.

# Load compiler-specific information.

set(_INCLUDED_FILE 0)  # reset the indicator if an include occurred.

if(CMAKE_D_COMPILER_ID)
  include(Compiler/${CMAKE_D_COMPILER_ID}-D OPTIONAL)
endif(CMAKE_D_COMPILER_ID)

# set(CMAKE_D_OUTPUT_EXTENSION .o)
set(CMAKE_C_OUTPUT_EXTENSION_REPLACE TRUE )
set(CMAKE_D_OUTPUT_EXTENSION_REPLACE TRUE )

set(CMAKE_BASE_NAME)
get_filename_component(CMAKE_BASE_NAME ${CMAKE_D_COMPILER} NAME_WE)

set(_INCLUDED_FILE 0)  # reset the indicator if an include occurred.

# load a hardware specific file, mostly useful for embedded compilers
if(CMAKE_SYSTEM_PROCESSOR)
  if(CMAKE_D_COMPILER_ID)
    include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_D_COMPILER_ID}-D-${CMAKE_SYSTEM_PROCESSOR} OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
  endif(CMAKE_D_COMPILER_ID)
  if(NOT _INCLUDED_FILE)
    include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_BASE_NAME}-${CMAKE_SYSTEM_PROCESSOR} OPTIONAL)
  endif(NOT _INCLUDED_FILE)
endif(CMAKE_SYSTEM_PROCESSOR)

set(_INCLUDED_FILE 0)  # reset the indicator if an include occurred.

# load the system- and compiler specific files
if(CMAKE_D_COMPILER_ID)
  include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_D_COMPILER_ID}-D
    OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
endif(CMAKE_D_COMPILER_ID)

# if no high specificity file was included, then try a more general one
if(NOT _INCLUDED_FILE)
  include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_BASE_NAME}
    OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
endif(NOT _INCLUDED_FILE)

# We specify the compiler information in the system file for some
# platforms, but this language may not have been enabled when the file
# was first included.  Include it again to get the language info.
# Remove this when all compiler info is removed from system files.
if(NOT _INCLUDED_FILE)
  include(Platform/${CMAKE_SYSTEM_NAME} OPTIONAL)
endif(NOT _INCLUDED_FILE)


# This should be included before the _INIT variables are
# used to initialize the cache.  Since the rule variables
# have if blocks on them, users can still define them here.
# But, it should still be after the platform file so changes can
# be made to those values.

if(CMAKE_USER_MAKE_RULES_OVERRIDE)
   include(${CMAKE_USER_MAKE_RULES_OVERRIDE})
endif(CMAKE_USER_MAKE_RULES_OVERRIDE)

if(CMAKE_USER_MAKE_RULES_OVERRIDE_D)
   include(${CMAKE_USER_MAKE_RULES_OVERRIDE_D})
endif(CMAKE_USER_MAKE_RULES_OVERRIDE_D)

# Lines below was taken from CMakeCXXInformation.cmake
# Not all of this flags are available on D compilers for now, but some as OPTIONS_PIC are.

if(NOT CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS)
   set(CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS ${CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS})
endif()

if(NOT CMAKE_D_COMPILE_OPTIONS_PIC)
   set(CMAKE_DCOMPILE_OPTIONS_PIC ${CMAKE_D_COMPILE_OPTIONS_PIC})
endif()

if(NOT CMAKE_D_COMPILE_OPTIONS_PIE)
   set(CMAKE_D_COMPILE_OPTIONS_PIE ${CMAKE_D_COMPILE_OPTIONS_PIE})
endif()

if(NOT CMAKE_D_COMPILE_OPTIONS_DLL)
   set(CMAKE_D_COMPILE_OPTIONS_DLL ${CMAKE_D_COMPILE_OPTIONS_DLL})
endif()

if(NOT CMAKE_SHARED_LIBRARY_D_FLAGS)
   set(CMAKE_SHARED_LIBRARY_D_FLAGS ${CMAKE_SHARED_LIBRARY_D_FLAGS})
endif()

if(NOT DEFINED CMAKE_SHARED_LIBRARY_LINK_D_FLAGS)
   set(CMAKE_SHARED_LIBRARY_LINK_D_FLAGS ${CMAKE_SHARED_LIBRARY_LINK_D_FLAGS})
endif()

if(NOT CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG)
   set(CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG ${CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG})
endif()

if(NOT CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG_SEP)
   set(CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG_SEP ${CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG_SEP})
endif()

if(NOT CMAKE_SHARED_LIBRARY_RPATH_LINK_D_FLAG)
  set(CMAKE_SHARED_LIBRARY_RPATH_LINK_D_FLAG ${CMAKE_SHARED_LIBRARY_RPATH_LINK_D_FLAG})
endif()

if(NOT DEFINED CMAKE_EXE_EXPORTS_D_FLAG)
  set(CMAKE_EXE_EXPORTS_D_FLAG ${CMAKE_EXE_EXPORTS_D_FLAG})
endif()

if(NOT DEFINED CMAKE_SHARED_LIBRARY_SONAME_D_FLAG)
   set(CMAKE_SHARED_LIBRARY_SONAME_D_FLAG ${CMAKE_SHARED_LIBRARY_SONAME_D_FLAG})
endif()

if(NOT CMAKE_EXECUTABLE_RUNTIME_D_FLAG)
  set(CMAKE_EXECUTABLE_RUNTIME_D_FLAG ${CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG})
endif()

if(NOT CMAKE_EXECUTABLE_RUNTIME_D_FLAG_SEP)
  set(CMAKE_EXECUTABLE_RUNTIME_D_FLAG_SEP ${CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG_SEP})
endif()

if(NOT CMAKE_EXECUTABLE_RPATH_LINK_D_FLAG)
  set(CMAKE_EXECUTABLE_RPATH_LINK_D_FLAG ${CMAKE_SHARED_LIBRARY_RPATH_LINK_D_FLAG})
endif()

if(NOT DEFINED CMAKE_SHARED_LIBRARY_LINK_D_WITH_RUNTIME_PATH)
  set(CMAKE_SHARED_LIBRARY_LINK_D_WITH_RUNTIME_PATH ${CMAKE_SHARED_LIBRARY_LINK_D_WITH_RUNTIME_PATH})
endif()

if(NOT CMAKE_INCLUDE_FLAG_D)
  set(CMAKE_INCLUDE_FLAG_D ${CMAKE_INCLUDE_FLAG_D})
endif()

if(NOT CMAKE_INCLUDE_FLAG_SEP_D)
  set(CMAKE_INCLUDE_FLAG_SEP_D ${CMAKE_INCLUDE_FLAG_SEP_D})
endif()

# for most systems a module is the same as a shared library
# so unless the variable CMAKE_MODULE_EXISTS is set just
# copy the values from the LIBRARY variables
if(NOT CMAKE_MODULE_EXISTS)
  set(CMAKE_SHARED_MODULE_D_FLAGS ${CMAKE_SHARED_LIBRARY_D_FLAGS})
  set(CMAKE_SHARED_MODULE_CREATE_D_FLAGS ${CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS})
endif(NOT CMAKE_MODULE_EXISTS)

# repeat for modules
if(NOT CMAKE_SHARED_MODULE_CREATE_D_FLAGS)
  set(CMAKE_SHARED_MODULE_CREATE_D_FLAGS ${CMAKE_SHARED_MODULE_CREATE_D_FLAGS})
endif()

if(NOT CMAKE_SHARED_MODULE_D_FLAGS)
  set(CMAKE_SHARED_MODULE_D_FLAGS ${CMAKE_SHARED_MODULE_D_FLAGS})
endif()

set(CMAKE_D_FLAGS_INIT "$ENV{DFLAGS} ${CMAKE_D_FLAGS_INIT}")
# avoid just having a space as the initial value for the cache
if(CMAKE_D_FLAGS_INIT STREQUAL " ")
  set(CMAKE_D_FLAGS_INIT)
endif(CMAKE_D_FLAGS_INIT STREQUAL " ")
set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS_INIT}" CACHE STRING
     "Flags used by the D compiler during all build types.")

if(NOT CMAKE_NOT_USING_CONFIG_FLAGS)
  # default build type is none
  if(NOT CMAKE_NO_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_INIT} CACHE STRING
      "Choose the type of build, options are: None(CMAKE_D_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
  endif(NOT CMAKE_NO_BUILD_TYPE)
  set(CMAKE_D_FLAGS_DEBUG "${CMAKE_D_FLAGS_DEBUG_INIT}" CACHE STRING
    "Flags used by the compiler during debug builds.")
  set(CMAKE_D_FLAGS_MINSIZEREL "${CMAKE_D_FLAGS_MINSIZEREL_INIT}" CACHE STRING
    "Flags used by the compiler during release minsize builds.")
  set(CMAKE_D_FLAGS_RELEASE "${CMAKE_D_FLAGS_RELEASE_INIT}" CACHE STRING
    "Flags used by the compiler during release builds (/MD /Ob1 /Oi /Ot /Oy /Gs will produce slightly less optimized but smaller files).")
  set(CMAKE_D_FLAGS_RELWITHDEBINFO "${CMAKE_D_FLAGS_RELWITHDEBINFO_INIT}" CACHE STRING
    "Flags used by the compiler during Release with Debug Info builds.")
endif(NOT CMAKE_NOT_USING_CONFIG_FLAGS)

if(CMAKE_D_STANDARD_LIBRARIES_INIT)
  set(CMAKE_D_STANDARD_LIBRARIES "${CMAKE_D_STANDARD_LIBRARIES_INIT}"
    CACHE STRING "Libraries linked by default with all D applications.")
  mark_as_advanced(CMAKE_D_STANDARD_LIBRARIES)
endif(CMAKE_D_STANDARD_LIBRARIES_INIT)

include(CMakeCommonLanguageInclude)

# now define the following rule variables

# CMAKE_D_CREATE_SHARED_LIBRARY
# CMAKE_D_CREATE_SHARED_MODULE
# CMAKE_D_CREATE_STATIC_LIBRARY
# CMAKE_D_COMPILE_OBJECT
# CMAKE_D_LINK_EXECUTABLE

# variables supplied by the generator at use time
# <TARGET>
# <TARGET_BASE> the target without the suffix
# <OBJECTS>
# <OBJECT>
# <LINK_LIBRARIES>
# <FLAGS>
# <LINK_FLAGS>

# D compiler information
# <CMAKE_D_COMPILER>
# <CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS>
# <CMAKE_SHARED_MODULE_CREATE_D_FLAGS>
# <CMAKE_D_LINK_FLAGS>

# Static library tools
# <CMAKE_AR>
# <CMAKE_RANLIB>

# < 2.8.10 backward compatibility
if(NOT CMAKE_PLATFORM_INFO_DIR)
  set(CMAKE_PLATFORM_INFO_DIR ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY})
endif(NOT CMAKE_PLATFORM_INFO_DIR)

# create a D shared library
if(NOT CMAKE_D_CREATE_SHARED_LIBRARY)
	set(CMAKE_D_CREATE_SHARED_LIBRARY
		"<CMAKE_D_COMPILER> <CMAKE_SHARED_LIBRARY_D_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS> <CMAKE_SHARED_LIBRARY_SONAME_D_FLAG><TARGET_SONAME> ${CMAKE_D_DASH_O}<TARGET> <OBJECTS> <LINK_LIBRARIES> ${DSTDLIB_FLAGS} ${CMAKE_D_STDLIBS}")
endif(NOT CMAKE_D_CREATE_SHARED_LIBRARY)

# create a D shared module just copy the shared library rule
if(NOT CMAKE_D_CREATE_SHARED_MODULE)
  set(CMAKE_D_CREATE_SHARED_MODULE "${CMAKE_D_CREATE_SHARED_LIBRARY}")
endif(NOT CMAKE_D_CREATE_SHARED_MODULE)

if(NOT CMAKE_D_CREATE_STATIC_LIBRARY AND CMAKE_STATIC_LIBRARY_CREATE_D_FLAGS)
	set(CMAKE_D_CREATE_STATIC_LIBRARY
		"<CMAKE_D_COMPILER> ${CMAKE_STATIC_LIBRARY_CREATE_D_FLAGS} <OBJECTS> ${CMAKE_D_DASH_O}<TARGET>")
endif(NOT CMAKE_D_CREATE_STATIC_LIBRARY AND CMAKE_STATIC_LIBRARY_CREATE_D_FLAGS)

# Create a static archive incrementally for large object file counts.
# If CMAKE_D_CREATE_STATIC_LIBRARY is set it will override these.
set(CMAKE_D_ARCHIVE_CREATE "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_D_ARCHIVE_APPEND "<CMAKE_AR> r  <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_D_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")

# compile a D file into an object file
if(NOT CMAKE_D_COMPILE_OBJECT)
    set(CMAKE_D_COMPILE_OBJECT
     "<CMAKE_D_COMPILER> <FLAGS> ${CMAKE_D_DASH_O}<OBJECT> -c <SOURCE>")
endif(NOT CMAKE_D_COMPILE_OBJECT)

if(NOT CMAKE_D_LINK_EXECUTABLE)
  set(CMAKE_D_LINK_EXECUTABLE
    "<CMAKE_D_COMPILER> <FLAGS> <CMAKE_D_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> ${CMAKE_D_DASH_O}<TARGET> <LINK_LIBRARIES> ${CMAKE_D_STDLIBS}")
endif(NOT CMAKE_D_LINK_EXECUTABLE)

mark_as_advanced(
CMAKE_D_FLAGS
CMAKE_D_FLAGS_DEBUG
CMAKE_D_FLAGS_MINSIZEREL
CMAKE_D_FLAGS_RELEASE
CMAKE_D_FLAGS_RELWITHDEBINFO
)
set(CMAKE_D_INFORMATION_LOADED 1)
