cmake_minimum_required(VERSION 3.16)
project(Lab7 C)

set(CMAKE_C_STANDARD 99)


add_executable(Lab7_Server server.c input.h task14.h task14.c timer.c timer.h logOutput.c logOutput.h input.c ServerFunctions.c ServerFunctions.h)
add_executable(Lab7_Client client.c input.h task14.h task14.c timer.c timer.h logOutput.c logOutput.h input.c)
target_link_libraries(Lab7_Server m)
target_link_libraries(Lab7_Client m)
