project(TestDynamicQObject)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-long-long -pedantic")
endif()

find_package(Qt5Test REQUIRED)

add_executable(${PROJECT_NAME} test_dynamicqobject.cpp)

target_link_libraries(${PROJECT_NAME} DOtherSideStatic Qt5::Test)
