cmake_minimum_required(VERSION 3.10)
project(LayoutConverter VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/inih)

set(SOURCES
    src/main.cpp
    src/convert_utils.cpp
    src/clipboard_utils.cpp
    src/layout_utils.cpp
    src/keyboard_hook.cpp
    libs/inih/ini.c
)

add_executable(LayoutConverter ${SOURCES})
target_link_libraries(LayoutConverter PRIVATE user32 shell32)