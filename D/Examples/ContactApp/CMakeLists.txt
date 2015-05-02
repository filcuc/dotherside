cmake_minimum_required(VERSION 3.0)
project (DQmlContactApp C D )
add_executable(${PROJECT_NAME} main.d applicationlogic.d contact.d contactlist.d)
target_include_directories(${PROJECT_NAME} PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/../../DQml"
  ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}/../../../DOtherSide/DOtherSide/libDOtherSide.so"
  "${CMAKE_CURRENT_BINARY_DIR}/../../DQml/libDQml.a"
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/main.qml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})