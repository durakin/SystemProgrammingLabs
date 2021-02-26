cmake_minimum_required(VERSION 3.17)
project(Lab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ChildProgram task14.c task14.h child.c)
target_link_libraries(ChildProgram m)