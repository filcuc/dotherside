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
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.1)
PROJECT (cmake-d NONE)

SET (MOD_SRCS
	CMakeDCompiler.cmake.in        
	CMakeDCompilerId.d.in        
	CMakeDInformation.cmake        
	CMakeDCompilerABI.d        
	CMakeTestDCompiler.cmake  
	CMakeDetermineDCompiler.cmake  
	FindGDCPath.cmake
	UseDDoc.cmake
	UseDDeps.cmake
	UseDub.cmake
	dependencies.cmake
	UseDUnittest.cmake
	FindPhobos.cmake
	CMakePlatformId.di.in
)

SET (PLAT_SRCS
	Platform/Linux-dmd.cmake
	Platform/Linux-gdc.cmake 
	Platform/Linux-ldc2.cmake 
	Platform/Windows-dmd.cmake              
	Platform/Windows-gdc.cmake
)

INSTALL (FILES ${MOD_SRCS} DESTINATION ${CMAKE_ROOT}/Modules)
INSTALL (FILES ${PLAT_SRCS} DESTINATION ${CMAKE_ROOT}/Modules/Platform)
