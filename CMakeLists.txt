#cmake_minimum_required(VERSION 3.29)
#project(hot100 C)
#
#set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
#
#include_directories(${PROJECT_SOURCE_DIR}/include)
#
#file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.c")
#
#set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
#file(MAKE_DIRECTORY ${OUTPUT_DIR})
#
#add_executable(main ${SRC_FILES})

cmake_minimum_required(VERSION 3.29)
project(hot100 CXX)  # 将项目语言从C改为CXX(C++)

set(CMAKE_CXX_STANDARD 17)  # 设置C++标准为17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制要求指定的C++标准

# 为不同编译器选择合适的警告选项（MSVC 不支持 -Wextra）
if (MSVC)
    # MSVC 常用警告等级为 /W3 或 /W4
    add_compile_options(/W4)
else()
    # 非 MSVC（如 GCC / Clang）使用 -Wall -Wextra
    add_compile_options(-Wall -Wextra)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

# 同时匹配C和CPP源文件
file(GLOB SRC_FILES CONFIGURE_DEPENDS
        "src/*.cpp"
)

set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
file(MAKE_DIRECTORY ${OUTPUT_DIR})

add_executable(main ${SRC_FILES})

