CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(NiftiReader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(ITK REQUIRED)
include(${ITK_USE_FILE})

file (
  GLOB_RECURSE
  source_files
  src/*
)

add_executable (
  niftireader
  main.cpp
  ${source_files}
)

target_link_libraries(niftireader ${ITK_LIBRARIES})

QT5_USE_MODULES(niftireader Widgets Core Gui)
