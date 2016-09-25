cmake_minimum_required(VERSION 3.6)
project(sar2_1UDP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES UDP/echo_cli_udp.c TCP/echo_ser_tcp.cpp TCP/echo_cli_tcp.cpp)
add_executable(sar2_1UDP ${SOURCE_FILES})