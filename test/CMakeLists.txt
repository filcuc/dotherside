project(TestDynamicQObject)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories(${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/lib/include/Qt)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Quick REQUIRED)

add_executable(${PROJECT_NAME} Resources.qrc test_dynamicqobject.cpp main.qml)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} DOtherSideStatic Qt5::Quick Qt5::Widgets Qt5::Test Qt5::Core)
