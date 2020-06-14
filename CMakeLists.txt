cmake_minimum_required(VERSION 2.8)
project(kdepim2google)

set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(BUILD_POSTFIX "_d")
else(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(BUILD_POSTFIX "")
endif(CMAKE_BUILD_TYPE STREQUAL Debug)
add_subdirectory(src)


add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake)
