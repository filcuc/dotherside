cmake_minimum_required(VERSION 3.0)
project (DQml C D )
add_library(${PROJECT_NAME} STATIC
  dqml.d
  qobject.d
  qslot.d
  qvariant.d
  qquickview.d
  qqmlapplicationengine.d
  qqmlcontext.d
  qsignal.d
  chararray.d
  qguiapplication.d
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
