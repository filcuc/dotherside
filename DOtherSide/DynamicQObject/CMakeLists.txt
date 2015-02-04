project(DynamicQObject)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(Qt5Core)

set(HEADERS_LIST
  DynamicProperty.h
  DynamicQObject.h
  DynamicSignal.h
  DynamicSlot.h
)

set(SRC_LIST 
  DynamicProperty.cpp
  DynamicSignal.cpp
  DynamicSlot.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST} ${HEADERS_LIST})
target_link_libraries(${PROJECT_NAME} Qt5::Core)
