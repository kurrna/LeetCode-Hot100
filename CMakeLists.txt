cmake_minimum_required(VERSION 3.29)
project(hot100 C)

set(CMAKE_C_STANDARD 11)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.c")

add_executable(main.exe ${SRC_FILES})
