cmake_minimum_required(VERSION 3.8)
project(ProgTest3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(ProgTest3 ${SOURCE_FILES})
target_link_libraries(ProgTest3 m)