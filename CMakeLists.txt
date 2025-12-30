cmake_minimum_required(VERSION 3.29)
project(hot100 LANGUAGES C CXX)  # 同时启用 C 与 C++

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 避免 gnu++ 扩展

# 配置 C23 标准（需编译器支持；MSVC 对 C23 可能暂不完全支持，GCC/Clang 新版本逐步完善）
#set(CMAKE_C_STANDARD 17)
#set(CMAKE_C_STANDARD_REQUIRED ON)
#set(CMAKE_C_EXTENSIONS OFF)  # 避免 gnu C 扩展

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
#file(GLOB C_SRC_FILES CONFIGURE_DEPENDS
#        "src/*.c"
#)

file(GLOB CXX_SRC_FILES CONFIGURE_DEPENDS
        "src/*.cpp"
        "include/*.cpp"
)
set(SRC_FILES ${C_SRC_FILES} ${CXX_SRC_FILES})

set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
file(MAKE_DIRECTORY ${OUTPUT_DIR})

add_executable(main ${SRC_FILES})
