cmake_minimum_required(VERSION 3.0)

set(BUILD_DQML FALSE CACHE BOOL "Enable the building of the D bindings")
set(BUILD_NIMQML FALSE CACHE BOOL "Enable the building of the Nim bindings")

add_subdirectory(DOtherSide)
if (BUILD_DQML)
  add_subdirectory(D)
endif()

if (BUILD_NIMQML)
  add_subdirectory(Nim)
endif()
