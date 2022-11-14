cmake_minimum_required(VERSION 3.9)
project(DearImGuiSDL)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(SDL2 
NAMES sdl2
HINTS ${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.9 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/library)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/library)

# Tests
link_libraries(DearImGuiSDL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)