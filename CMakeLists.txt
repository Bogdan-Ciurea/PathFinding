cmake_minimum_required(VERSION 3.12)
project(CyberRoads C)

set(CMAKE_C_STANDARD 11)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# Include directories
include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

# Console log SDL2_INCLUDE_DIRS
# message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
# message(STATUS "SDL2IMAGE_INCLUDE_DIRS: ${SDL2IMAGE_INCLUDE_DIRS}")
# message(STATUS "SDL2TTF_INCLUDE_DIRS: ${SDL2TTF_INCLUDE_DIRS}")

# Add your source files
set(SOURCES
     bellman_ford.c
     dijkstra.c
     functions.h
     globalFunctions.c
     main.c
     reading.c
     sdl_functions.c
)

# Add an executable target
add_executable(CyberRoads ${SOURCES})

# Specify SDL2 library path
if(WIN32)
     set(SDL2_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets/SDL2.dll)
endif()
if(UNIX AND NOT APPLE)
     set(SDL2_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets/libSDL2.so)
endif()
if (APPLE)
     set(SDL2_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets/mac/libSDL2-2.0.0.dylib 
          ${CMAKE_CURRENT_SOURCE_DIR}/assets/mac/libSDL2_ttf-2.0.0.dylib)
endif()

# Link SDL2 library
target_link_libraries(CyberRoads PRIVATE ${SDL2_LIB_PATH})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/Final_Map.map DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/OpenSans.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})