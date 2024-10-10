cmake_minimum_required(VERSION 3.20)
project(Siesta)

option(SIESTA_BUILD_EXAMPLES "Whether to build example projects" ON)
option(SIESTA_BUILD_EDITOR "Whether to build the editor" ON)

include(Siesta/CMake/Siesta.cmake)

add_subdirectory(Siesta)