cmake_minimum_required(VERSION 3.16)
project(Lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab2 main.c task11.h task11.c thread.h thread.c)
target_link_libraries(Lab2 PRIVATE pthread)
