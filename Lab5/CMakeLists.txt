cmake_minimum_required(VERSION 3.16)
project(Lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab5_Server server.c)
add_executable(Lab5_Client client.c)