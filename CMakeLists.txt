cmake_minimum_required(VERSION 3.15)
project(core2d)

set(MAIN src/main.cpp)
set(CORE2D_SRC )

# Add all src/c2d*.h files to CORE2D_SRC
file(GLOB CORE2D_ALL_SOURCES src/c2d_*.c)
list(APPEND CORE2D_SRC ${CORE2D_ALL_SOURCES})

add_library(core2d STATIC ${CORE2D_SRC})

add_executable(test ${MAIN})

target_link_libraries(test core2d SDL2 SDL2_image SDL2_ttf SDL2_mixer)