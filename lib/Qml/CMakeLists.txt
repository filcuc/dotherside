find_package(Qt5Qml REQUIRED)

set(TARGET_SOURCES include/DOtherSide/Qml/Qml.h)
set(TARGET_INCLUDES src/QQmlApplicationEngine.cpp)

include_directories(include)

add_library(DOtherSideQml ${TARGET_SOURCES} ${TARGET_INCLUDES})
target_link_libraries(DOtherSideQml Qt5::Qml)

