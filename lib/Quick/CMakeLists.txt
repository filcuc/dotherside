find_package(Qt5Quick REQUIRED)

set(TARGET_SOURCES include/DOtherSide/Quick/Quick.h)
set(TARGET_INCLUDES src/QQuickView.cpp)

include_directories(include)

add_library(DOtherSideQuick ${TARGET_SOURCES} ${TARGET_INCLUDES})
target_link_libraries(DOtherSideQuick Qt5::Quick)
