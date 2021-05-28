cmake_minimum_required(VERSION 3.16)
project(Lab8 C)

set(CMAKE_C_STANDARD 99)


add_executable(Lab8_Server server.c input.h task14.h task14.c timer.c timer.h logOutput.c logOutput.h input.c ServerFunctions.c ServerFunctions.h securityFunctions.c securityFunctions.h)
add_executable(Lab8_Client client.c input.h task14.h task14.c timer.c timer.h logOutput.c logOutput.h input.c securityFunctions.c securityFunctions.h)
target_link_libraries(Lab8_Server m)
target_link_libraries(Lab8_Client m)
