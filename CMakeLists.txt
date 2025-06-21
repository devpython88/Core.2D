cmake_minimum_required(VERSION 3.15)
project(core2d)

set(MAIN src/main.cpp)
set(CORE2D_H src/core2d.h)
set(CORE2D_SRC src/c2dwindow.c)

add_library(core2d STATIC ${CORE2D_SRC})

add_executable(test ${MAIN})

target_link_libraries(test core2d SDL2)