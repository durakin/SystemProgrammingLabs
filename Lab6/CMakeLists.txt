cmake_minimum_required(VERSION 3.16)
project(Lab5 C)

set(CMAKE_C_STANDARD 99)


add_executable(Lab5_Server server.c input.h task14.h task14.c timer.c timer.h logOutput.c logOutput.h)
add_executable(Lab5_Client client.c input.h task14.h task14.c timer.c timer.h logOutput.c logOutput.h)
target_link_libraries(Lab5_Server m)
target_link_libraries(Lab5_Client m)
