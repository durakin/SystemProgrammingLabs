cmake_minimum_required(VERSION 3.17)
project(Lab1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Tests main.c ../ChildProgram/task14.c)
target_link_libraries(Tests cunit)
target_link_libraries(Tests cunit m)