find_package(Qt5Widgets REQUIRED)

set(TARGET_SOURCES include/DOtherSide/Widgets/Widgets.h)
set(TARGET_INCLUDES src/QApplication.cpp)

include_directories(include)

add_library(DOtherSideWidgets ${TARGET_SOURCES} ${TARGET_INCLUDES})
target_link_libraries(DOtherSideWidgets Qt5::Widgets)
