project(IntegrationTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Qt5Gui)
find_package(Qt5Qml)
find_package(Qt5Declarative)

set(RESOURCE_LIST
  qml.qrc
)

set(HEADERS_LIST
)

set(SRC_LIST 
  main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST} ${RESOURCE_LIST})
target_link_libraries(${PROJECT_NAME} Qt5::Gui Qt5::Qml DynamicQObject)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../DynamicQObject)