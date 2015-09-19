project(DOtherSide)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-long-long -pedantic")
endif()

if (WIN32)
    add_definitions(-DWIN32)
endif()

find_package(Qt5Core)
find_package(Qt5Qml)
find_package(Qt5Gui)
find_package(Qt5Quick)
find_package(Qt5Widgets)

set(HEADERS_LIST
    BaseQAbstractListModel.h
    DOtherSideTypes.h
    DynamicSignal.h
    BaseQObject.h
    DynamicProperty.h
    DynamicSlot.h
    DOtherSide.h
    DynamicQObject.h
    IDynamicQObject.h
)

set(SRC_LIST 
    DOtherSide.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${HEADERS_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Qml Qt5::Quick)
