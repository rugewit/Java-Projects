cmake_minimum_required(VERSION 3.17)
project(Lab3 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

find_package (Threads)
add_executable(Lab3 parallel.c matrix.h)

target_link_libraries (Lab3 ${CMAKE_THREAD_LIBS_INIT} m)