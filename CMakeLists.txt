cmake_minimum_required (VERSION 3.0)
SET(CMAKE_CXX_STANDARD 11)

project (tlk-utils)

file(GLOB_RECURSE lib_sources "lib/*.cpp")

add_executable(tlkview ${lib_sources} utils/tlkview.cpp)
target_include_directories(tlkview PUBLIC lib)

add_executable(tlkcombine ${lib_sources} utils/tlkcombine.cpp)
target_include_directories(tlkcombine PUBLIC lib)

add_executable(tlkreplace ${lib_sources} utils/tlkreplace.cpp)
target_include_directories(tlkreplace PUBLIC lib)

add_executable(tlkappend ${lib_sources} utils/tlkappend.cpp)
target_include_directories(tlkappend PUBLIC lib)

add_executable(tlksearch ${lib_sources} utils/tlksearch.cpp)
target_include_directories(tlksearch PUBLIC lib)
