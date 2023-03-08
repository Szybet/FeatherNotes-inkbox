project(feathernotes)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Release)
add_definitions(-Wall)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_QT5 "Building Qt5 plugin." ON)
option(WITH_HUNSPELL "Compiling with Hunspell..." OFF)
option(WITHOUT_X11 "Compiling without X11..." ON)

add_subdirectory(feathernotes)
