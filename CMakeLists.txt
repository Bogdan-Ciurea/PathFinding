cmake_minimum_required(VERSION 2.8)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

project(CyberRoads)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")

include_directories(Unity/include)

add_executable(path main.c reading.c SDLFunctions.c Dijkstra.c BellmanFord.c globalFunctions.c)
add_executable(unit_tests unit_tests.c reading.c SDLFunctions.c Dijkstra.c BellmanFord.c globalFunctions.c unity/src/unity.c)

target_include_directories(path PRIVATE include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(path PRIVATE ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

target_include_directories(unit_tests PRIVATE include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(unit_tests PRIVATE ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})


install(TARGETS path RUNTIME DESTINATION bin)
install(TARGETS unit_tests RUNTIME DESTINATION bin)

