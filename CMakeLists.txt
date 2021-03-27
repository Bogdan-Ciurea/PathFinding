cmake_minimum_required(VERSION 2.8)

project(CyberRoads)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")

include_directories(unity/include)

add_executable(path main.c reading.c SDLFunctions.c Dijkstra.c BellmanFord.c globalFunctions.c)

add_executable(unit_tests unit_tests.c reading.c SDLFunctions.c Dijkstra.c BellmanFord.c globalFunctions.c unity/src/unity.c)

install(TARGETS path RUNTIME DESTINATION bin)


