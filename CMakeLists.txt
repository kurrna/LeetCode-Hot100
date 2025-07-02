cmake_minimum_required(VERSION 3.29)
project(hot100 C)

set(CMAKE_C_STANDARD 11)

add_executable(hot100
    finished/*.c
    *.c)
