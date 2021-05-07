cmake_minimum_required(VERSION 3.16)
project(Lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab5_Server server.c task14.c task14.c socketOperations.c socketOperations.h serverSocketInterface.c serverConsoleInterface.h)
add_executable(Lab5_Client client.c task14.h task14.c input.h input.c socketOperations.c socketOperations.h clientSocketInterface.c clientSocketInterface.h)
target_link_libraries(Lab5_Server m)
target_link_libraries(Lab5_Client m)