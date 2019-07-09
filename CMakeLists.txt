cmake_minimum_required(VERSION 3.10.2)

project(AutomataDungeone)

set(SOURCE_FILES main.cpp)

#link_libraries()

add_executable(AutomataDungeone ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

#add_executable(TestNaive Test/naive.c)
#add_test(TestCountBits "./Naive")

