cmake_minimum_required(VERSION 3.29)
project(hot100 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.c")

set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
file(MAKE_DIRECTORY ${OUTPUT_DIR})

add_executable(main ${SRC_FILES})
