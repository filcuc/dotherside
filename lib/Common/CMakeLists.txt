set(TARGET_SOURCES include/DOtherSide/Common/Common.h)
set(TARGET_INCLUDES src/Common.cpp)

include_directories(include)

add_library(DOtherSideCommon STATIC ${TARGET_SOURCES} ${TARGET_INCLUDES})

