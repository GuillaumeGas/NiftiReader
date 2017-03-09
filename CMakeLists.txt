CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
project(NiftiReader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")

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