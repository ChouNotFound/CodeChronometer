# 添加最低CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 修改项目名称为更具描述性的名称
project(CodeStatisticsSystem C)  # 更明确的项目名称

# 添加C标准支持
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# 使用更现代的编译器选项
include_directories(include)

# 收集源文件（使用更明确的模式）
file(GLOB_RECURSE SRC_FILES "src/*.c")

add_executable(${PROJECT_NAME} ${SRC_FILES})

# 添加编译定义以支持Windows API
if(WIN32)
    add_definitions(-D_WIN32)
    # 链接kernel32库以使用Sleep函数
    target_link_libraries(${PROJECT_NAME} PRIVATE kernel32)
endif()

# 优化编译选项
if(MSVC)
    add_compile_options(/Wall /Wextra /Wpedantic /Wshadow /Wunreachable-code)
else()
    add_compile_options(-Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wconversion)
    add_compile_options(-mconsole)
    add_compile_options(-O2)  # 添加优化选项
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)  # 明确指定字符集
endif()