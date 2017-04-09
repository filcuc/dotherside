find_package(Qt5Gui REQUIRED)

set(TARGET_SOURCES include/DOtherSide/Gui/Gui.h)
set(TARGET_INCLUDES src/QGuiApplication.cpp)

include_directories(include)

add_library(DOtherSideGui ${TARGET_SOURCES} ${TARGET_INCLUDES})
target_link_libraries(DOtherSideGui Qt5::Gui)
