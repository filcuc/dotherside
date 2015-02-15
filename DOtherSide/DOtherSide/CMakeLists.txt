project(DOtherSide)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Gui)
find_package(Qt5Quick)
find_package(Qt5Widgets)

set(HEADERS_LIST
  DOtherSide.h
  DOtherSideTypes.h
  BaseQAbstractListModel.h
  BaseQObject.h
)

set(SRC_LIST 
  DOtherSide.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${HEADERS_LIST})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Qml Qt5::Quick)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../DynamicQObject)