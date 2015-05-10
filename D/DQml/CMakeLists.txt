cmake_minimum_required(VERSION 3.0)
project (DQml C D )
add_library(${PROJECT_NAME} STATIC
  dqml.d
  qobject.d
  qvariant.d
  qmetatype.d
  qquickview.d
  qqmlapplicationengine.d
  qqmlcontext.d
  qguiapplication.d
  qapplication.d
  qmodelindex.d
  qabstractlistmodel.d
  qobjectgenerators.d
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
