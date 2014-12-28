#
# CMakeD - CMake module for D Language
#
# Copyright (c) 2013, Selman Ulug <selman.ulug@gmail.com>
#                     Tim Burrell <tim.burrell@gmail.com>
#                     Dragos Carp <dragos.carp@gmail.com>
#
# All rights reserved.
#
# See LICENSE for details.
#
# Modified from CMake 2.6.5 CMakeDetermineCCompiler.cmake
# See http://www.cmake.org/HTML/Copyright.html for details
#

# determine the compiler to use for D programs
# NOTE, a generator may set CMAKE_D_COMPILER before
# loading this file to force a compiler.
# use environment variable DC first if defined by user, next use
# the cmake variable CMAKE_GENERATOR_D which can be defined by a generator
# as a default compiler

if(NOT CMAKE_D_COMPILER)
  set(CMAKE_D_COMPILER_INIT NOTFOUND)
  # prefer the environment variable DC
  if($ENV{DC} MATCHES ".+")
    get_filename_component(CMAKE_D_COMPILER_INIT $ENV{DC} PROGRAM PROGRAM_ARGS CMAKE_D_FLAGS_ENV_INIT)
    if(CMAKE_D_FLAGS_ENV_INIT)
      set(CMAKE_D_COMPILER_ARG1 "${CMAKE_D_FLAGS_ENV_INIT}" CACHE STRING "First argument to D compiler")
    endif(CMAKE_D_FLAGS_ENV_INIT)
    if(NOT EXISTS ${CMAKE_D_COMPILER_INIT})
      MESSAGE(FATAL_ERROR "Could not find compiler set in environment variable C:\n$ENV{DC}.")
    endif(NOT EXISTS ${CMAKE_D_COMPILER_INIT})
  endif($ENV{DC} MATCHES ".+")

  # next try prefer the compiler specified by the generator
  if(CMAKE_GENERATOR_D)
    if(NOT CMAKE_D_COMPILER_INIT)
      set(CMAKE_D_COMPILER_INIT ${CMAKE_GENERATOR_D})
    endif(NOT CMAKE_D_COMPILER_INIT)
  endif(CMAKE_GENERATOR_D)

  # finally list compilers to try
  if(CMAKE_D_COMPILER_INIT)
    set(CMAKE_D_COMPILER_LIST ${CMAKE_D_COMPILER_INIT})
  else(CMAKE_D_COMPILER_INIT)
    set(CMAKE_D_COMPILER_LIST ${_CMAKE_TOOLCHAIN_PREFIX}gdc ${_CMAKE_TOOLCHAIN_PREFIX}dmd)
  endif(CMAKE_D_COMPILER_INIT)

  # Find the compiler.
  if(_CMAKE_USER_D_COMPILER_PATH)
  	find_program(CMAKE_D_COMPILER NAMES ${CMAKE_D_COMPILER_LIST} PATHS ${_CMAKE_USER_D_COMPILER_PATH} DOC "D compiler" NO_DEFAULT_PATH)
  endif(_CMAKE_USER_D_COMPILER_PATH)
  find_program(CMAKE_D_COMPILER NAMES ${CMAKE_D_COMPILER_LIST} DOC "D compiler")

  if(CMAKE_D_COMPILER_INIT AND NOT CMAKE_D_COMPILER)
    set(CMAKE_D_COMPILER "${CMAKE_D_COMPILER_INIT}" CACHE FILEPATH "D compiler" FORCE)
  endif(CMAKE_D_COMPILER_INIT AND NOT CMAKE_D_COMPILER)
else(NOT CMAKE_D_COMPILER)

  # we only get here if CMAKE_D_COMPILER was specified using -D or a pre-made CMakeCache.txt
  # (e.g. via ctest) or set in CMAKE_TOOLCHAIN_FILE
  # if CMAKE_D_COMPILER is a list of length 2, use the first item as
  # CMAKE_D_COMPILER and the 2nd one as CMAKE_D_COMPILER_ARG1

  list(LENGTH CMAKE_D_COMPILER _CMAKE_D_COMPILER_LIST_LENGTH)
  if("${_CMAKE_D_COMPILER_LIST_LENGTH}" EQUAL 2)
    list(GET CMAKE_D_COMPILER 1 CMAKE_D_COMPILER_ARG1)
    list(GET CMAKE_D_COMPILER 0 CMAKE_D_COMPILER)
  endif("${_CMAKE_D_COMPILER_LIST_LENGTH}" EQUAL 2)

  # if a compiler was specified by the user but without path,
  # now try to find it with the full path
  # if it is found, force it into the cache,
  # if not, don't overwrite the setting (which was given by the user) with "NOTFOUND"
  # if the C compiler already had a path, reuse it for searching the CXX compiler
  get_filename_component(_CMAKE_USER_D_COMPILER_PATH "${CMAKE_D_COMPILER}" PATH)
  if(NOT _CMAKE_USER_D_COMPILER_PATH)
    find_program(CMAKE_D_COMPILER_WITH_PATH NAMES ${CMAKE_D_COMPILER})
    mark_as_advanced(CMAKE_D_COMPILER_WITH_PATH)
    if(CMAKE_D_COMPILER_WITH_PATH)
      set(CMAKE_D_COMPILER ${CMAKE_D_COMPILER_WITH_PATH} CACHE STRING "D compiler" FORCE)
    endif(CMAKE_D_COMPILER_WITH_PATH)
  endif(NOT _CMAKE_USER_D_COMPILER_PATH)
endif(NOT CMAKE_D_COMPILER)
mark_as_advanced(CMAKE_D_COMPILER)

if(NOT _CMAKE_TOOLCHAIN_LOCATION)
  get_filename_component(_CMAKE_TOOLCHAIN_LOCATION "${CMAKE_D_COMPILER}" PATH)
endif(NOT _CMAKE_TOOLCHAIN_LOCATION)

# Build a small source file to identify the compiler.
if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
  set(CMAKE_D_COMPILER_ID_RUN 1)
  set(CMAKE_D_PLATFORM_ID "Windows")

  # TODO: Set the compiler id.  It is probably MSVC but
  # the user may be using an integrated Intel compiler.
  # set(CMAKE_D_COMPILER_ID "MSVC")
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio")

if(NOT CMAKE_D_COMPILER_ID_RUN)
  set(CMAKE_D_COMPILER_ID_RUN 1)

  # Each entry in this list is a set of extra flags to try
  # adding to the compile line to see if it helps produce
  # a valid identification file.
  set(CMAKE_D_COMPILER_ID_TEST_FLAGS
    # Try compiling to an object file only.
    "-c"
    )

  # Try to identify the compiler.
  set(CMAKE_D_COMPILER_ID)
  find_file(CMAKE_PLATFORM_ID_CONTENT_FILE CMakePlatformId.di.in PATHS ${CMAKE_ROOT}/Modules
    ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
  file(READ ${CMAKE_PLATFORM_ID_CONTENT_FILE} CMAKE_D_COMPILER_ID_PLATFORM_CONTENT)
  find_file(CMAKE_D_COMPILER_ID_FILE_IN CMakeDCompilerId.d.in PATHS ${CMAKE_ROOT}/Modules
    ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
  # Workaround for bug http://public.kitware.com/Bug/view.php?id=14481
  # if CMAKE_MODULE_PATH is used, then patch ${CMAKE_ROOT}/Modules/CMakeDetermineCompilerId.cmake
  get_filename_component(CMAKE_D_COMPILER_ID_FILE_IN_PATH ${CMAKE_D_COMPILER_ID_FILE_IN} PATH)
  if(CMAKE_MAJOR_VERSION GREATER 2 OR CMAKE_D_COMPILER_ID_FILE_IN_PATH STREQUAL ${CMAKE_ROOT}/Modules)
    include(${CMAKE_ROOT}/Modules/CMakeDetermineCompilerId.cmake)
  else(CMAKE_D_COMPILER_ID_FILE_IN_PATH STREQUAL ${CMAKE_ROOT}/Modules)
    file(READ ${CMAKE_ROOT}/Modules/CMakeDetermineCompilerId.cmake CMAKE_DETERMINE_COMPILER_ID_CMAKE_CONTENT)
    STRING(REPLACE "file(READ \${CMAKE_ROOT}/Modules/\${src}.in ID_CONTENT_IN)" 
      "find_file(src_in \${src}.in PATHS \${CMAKE_ROOT}/Modules \${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
  file(READ \${src_in} ID_CONTENT_IN)
  unset(src_in CACHE)"
    CMAKE_DETERMINE_COMPILER_ID_CMAKE_CONTENT_PATCHED ${CMAKE_DETERMINE_COMPILER_ID_CMAKE_CONTENT})
    file(WRITE ${CMAKE_PLATFORM_INFO_DIR}/CMakeDetermineCompilerId.cmake
      ${CMAKE_DETERMINE_COMPILER_ID_CMAKE_CONTENT_PATCHED})
    include(${CMAKE_PLATFORM_INFO_DIR}/CMakeDetermineCompilerId.cmake)
  endif(CMAKE_MAJOR_VERSION GREATER 2 OR CMAKE_D_COMPILER_ID_FILE_IN_PATH STREQUAL ${CMAKE_ROOT}/Modules)
  CMAKE_DETERMINE_COMPILER_ID(D DFLAGS CMakeDCompilerId.d)
  unset(CMAKE_D_COMPILER_ID_FILE_IN CACHE)
  unset(CMAKE_PLATFORM_ID_CONTENT_FILE CACHE)

  # Set old compiler and platform id variables.
  if("${CMAKE_D_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_COMPILER_IS_GDC 1)
  endif("${CMAKE_D_COMPILER_ID}" MATCHES "GNU")
  if("${CMAKE_D_PLATFORM_ID}" MATCHES "MinGW")
    set(CMAKE_COMPILER_IS_MINGW 1)
  elseif("${CMAKE_D_PLATFORM_ID}" MATCHES "Cygwin")
    set(CMAKE_COMPILER_IS_CYGWIN 1)
  endif("${CMAKE_D_PLATFORM_ID}" MATCHES "MinGW")
endif(NOT CMAKE_D_COMPILER_ID_RUN)

include(CMakeFindBinUtils)
if(MSVC_D_ARCHITECTURE_ID)
  set(SET_MSVC_D_ARCHITECTURE_ID
    "set(MSVC_D_ARCHITECTURE_ID ${MSVC_D_ARCHITECTURE_ID})")
endif(MSVC_D_ARCHITECTURE_ID)
# configure variables set in this file for fast reload later on
find_file(CMAKE_D_COMPILER_CMAKE_IN CMakeDCompiler.cmake.in PATHS ${CMAKE_ROOT}/Modules
  ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
configure_file(${CMAKE_D_COMPILER_CMAKE_IN}
  ${CMAKE_PLATFORM_INFO_DIR}/CMakeDCompiler.cmake
  @ONLY IMMEDIATE # IMMEDIATE must be here for compatibility mode <= 2.0
  )
set(CMAKE_D_COMPILER_ENV_VAR "DC")
