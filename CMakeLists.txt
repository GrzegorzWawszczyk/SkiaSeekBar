cmake_minimum_required(VERSION 3.21)
project(SkiaSeekBar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(PLATFORM "Target platform: windows or android" "windows")

message(STATUS "Target platform: ${PLATFORM}")

find_package(SDL3 CONFIG REQUIRED)
find_package(unofficial-skia CONFIG REQUIRED)

add_subdirectory(core)

if(PLATFORM STREQUAL "windows")
    add_subdirectory(platform/windows)
elseif(PLATFORM STREQUAL "android")
    add_subdirectory(platform/android)
else()
    message(FATAL_ERROR "Unknown PLATFORM: ${PLATFORM}")
endif()