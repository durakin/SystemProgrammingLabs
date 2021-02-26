cmake_minimum_required(VERSION 3.17)
project(Lab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ChildProgram child.c task14.h task14.c input.h input.c)
target_link_libraries(ChildProgram m)