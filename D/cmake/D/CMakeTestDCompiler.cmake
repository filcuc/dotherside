#
# CMakeD - CMake module for D Language
#
# Copyright (c) 2007, Selman Ulug <selman.ulug@gmail.com>
#                     Tim Burrell <tim.burrell@gmail.com>
#                     Dragos Carp <dragos.carp@gmail.com>
#
# All rights reserved.
#
# See LICENSE for details.
#
# Modified from CMake 2.6.5 CMakeTestCCompiler.cmake
# See http://www.cmake.org/HTML/Copyright.html for details
#

include(CMakeTestCompilerCommon)

# This file is used by EnableLanguage in cmGlobalGenerator to
# determine that that selected D compiler can actually compile
# and link the most basic of programs.   If not, a fatal error
# is set and cmake stops processing commands and will not generate
# any makefiles or projects.
if(NOT CMAKE_D_COMPILER_WORKS)
  PrintTestCompilerStatus("D" "")
  file(WRITE ${CMAKE_PLATFORM_INFO_DIR}/CMakeTmp/testDCompiler.d
    "int main(char[][] args)\n"
    "{return args.sizeof-1;}\n")
  try_compile(CMAKE_D_COMPILER_WORKS ${CMAKE_BINARY_DIR}
    ${CMAKE_PLATFORM_INFO_DIR}/CMakeTmp/testDCompiler.d
    OUTPUT_VARIABLE OUTPUT)
  set(D_TEST_WAS_RUN 1)
endif(NOT CMAKE_D_COMPILER_WORKS)

if(NOT CMAKE_D_COMPILER_WORKS)
  PrintTestCompilerStatus("D" " -- broken")
  message(STATUS "To force a specific D compiler set the DC environment variable")
  message(STATUS "    ie - export DC=\"/usr/bin/dmd\"")
  file(APPEND ${CMAKE_PLATFORM_INFO_DIR}/CMakeError.log
    "Determining if the D compiler works failed with "
    "the following output:\n${OUTPUT}\n\n")
  # if the compiler is broken make sure to remove the platform file
  # since Windows-cl configures both c/cxx files both need to be removed
  # when c or c++ fails
  file(REMOVE ${CMAKE_PLATFORM_INFO_DIR}/CMakeDPlatform.cmake)
  message(FATAL_ERROR "The D compiler \"${CMAKE_D_COMPILER}\" "
    "is not able to compile a simple test program.\nIt fails "
    "with the following output:\n ${OUTPUT}\n\n"
    "CMake will not be able to correctly generate this project.")
else(NOT CMAKE_D_COMPILER_WORKS)
  if(D_TEST_WAS_RUN)
    message(STATUS "Check for working D compiler: ${CMAKE_D_COMPILER} -- works")
    file(APPEND ${CMAKE_PLATFORM_INFO_DIR}/CMakeOutput.log
      "Determining if the D compiler works passed with "
      "the following output:\n${OUTPUT}\n\n")
  endif(D_TEST_WAS_RUN)
  set(CMAKE_D_COMPILER_WORKS 1 CACHE INTERNAL "")

  if(CMAKE_D_COMPILER_FORCED)
    # The compiler configuration was forced by the user.
    # Assume the user has configured all compiler information.
  else(CMAKE_D_COMPILER_FORCED)
    # Try to identify the ABI and configure it into CMakeDCompiler.cmake
    include(${CMAKE_ROOT}/Modules/CMakeDetermineCompilerABI.cmake)
    find_file(CMAKE_D_COMPILER_ABI_SRC CMakeDCompilerABI.d PATHS ${CMAKE_ROOT}/Modules
      ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
    CMAKE_DETERMINE_COMPILER_ABI(D ${CMAKE_D_COMPILER_ABI_SRC})
    find_file(CMAKE_D_COMPILER_CMAKE_IN CMakeDCompiler.cmake.in PATHS ${CMAKE_ROOT}/Modules
      ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
    configure_file(
      ${CMAKE_D_COMPILER_CMAKE_IN}
      ${CMAKE_PLATFORM_INFO_DIR}/CMakeDCompiler.cmake
      @ONLY IMMEDIATE # IMMEDIATE must be here for compatibility mode <= 2.0
      )
    include(${CMAKE_PLATFORM_INFO_DIR}/CMakeDCompiler.cmake)
    unset(CMAKE_D_COMPILER_ABI_SRC CACHE)
    unset(CMAKE_D_COMPILER_CMAKE_IN CACHE)
  endif(CMAKE_D_COMPILER_FORCED)
endif(NOT CMAKE_D_COMPILER_WORKS)
