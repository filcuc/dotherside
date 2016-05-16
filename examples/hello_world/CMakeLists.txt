cmake_minimum_required(VERSION 3.0)
project(hello)

include_directories(${CMAKE_SOURCE_DIR}/lib/include)

if (WIN32)
   set (PROJECT_LINK_LIBS DOtherSide)
else()
   set (PROJECT_LINK_LIBS libDOtherSide.so)
endif()
link_directories(${CMAKE_BINARY_DIR}/lib)

add_executable(${PROJECT_NAME} main.c)
add_dependencies(${PROJECT_NAME} DOtherSide)

target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
