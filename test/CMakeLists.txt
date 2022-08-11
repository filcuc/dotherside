project(TestDynamicQObject)

set(QTPREFIX "Qt")

find_package(Qt6 COMPONENTS Core Qml Gui Quick QuickControls2 Widgets Test)
if (NOT Qt6_FOUND)
    set(QTPREFIX "Qt5")
    find_package(Qt5 COMPONENTS Core Qml Gui Quick QuickControls2 Widgets Test)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} Resources.qrc
    test_dotherside.cpp
    MockQObject.h
    MockQObject.cpp
    MockQAbstractItemModel.h
    MockQAbstractItemModel.cpp
    Global.h
    main.qml
    testQObject.qml
    testQAbstractItemModel.qml
    testQDeclarative.qml
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
target_link_libraries(${PROJECT_NAME} DOtherSideStatic ${QTPREFIX}::Quick ${QTPREFIX}::Widgets ${QTPREFIX}::Test ${QTPREFIX}::Core)
