cmake_minimum_required(VERSION 2.8)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

project(CyberRoads)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")

include_directories(unity/include)
include_directories(unity/src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/Final_Map.map
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/SDL2.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/SDL2_ttf.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/SDL2_image.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/libfreetype-6.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/zlib1.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/OpenSans.ttf
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(path main.c reading.c sdl_functions.c dijkstra.c bellman_ford.c globalFunctions.c)
add_executable(unit_tests unit_tests.c reading.c sdl_functions.c dijkstra.c bellman_ford.c globalFunctions.c unity/src/unity.c)

target_include_directories(path PRIVATE include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(path PRIVATE ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

target_include_directories(unit_tests PRIVATE include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(unit_tests PRIVATE ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})


install(TARGETS path RUNTIME DESTINATION bin)
install(TARGETS unit_tests RUNTIME DESTINATION bin)

