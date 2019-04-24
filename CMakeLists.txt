cmake_minimum_required(VERSION 3.0)

# Options
option(ENABLE_COVERAGE "Enable coverage" OFF)
option(ENABLE_DOCS "Enable docs" ON)
option(ENABLE_TESTS "Enable tests" ON)
option(ENABLE_STATIC_LIBS "Enable static libraries" ON)

# Add additional source path for cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/)

# Add strict warning checking for C++
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

if(ENABLE_COVERAGE)
  message(STATUS "Enabling coverage")
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

# Add additional source path for cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/)

# Subdirectories
add_subdirectory(lib)

if(ENABLE_DOCS)
  add_subdirectory(doc)
endif()

if(ENABLE_TESTS)
  add_subdirectory(test)
endif()

