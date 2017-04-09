find_package(Qt5Core REQUIRED)

set(TARGET_SOURCES include/DOtherSide/Core/Core.h)
set(TARGET_INCLUDES src/QCoreApplication.cpp)

include_directories(include)

add_library(DOtherSideCore ${TARGET_SOURCES} ${TARGET_INCLUDES})
target_link_libraries(DOtherSideCore Qt5::Core)
