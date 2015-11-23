project(TestDynamicQObject)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/lib/include/Qt)

find_package(Qt5Test REQUIRED)

add_executable(${PROJECT_NAME} test_dynamicqobject.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} DOtherSideStatic Qt5::Test)
