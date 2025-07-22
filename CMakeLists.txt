cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(StudentManagement)

# 设置C语言标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 添加可执行文件
add_executable(student_management src/main.c src/student_management.c src/code_count.c)

# 添加编译选项
if(MSVC)
    add_compile_options(/Wall)
else()
    add_compile_options(-Wall -Wextra -pedantic)
    # MinGW特定编译选项
    add_compile_options(-mwindows -mconsole)
endif()

# MinGW特定链接选项
if(CMAKE_COMPILER_IS_GNUCC)
    target_link_libraries(student_management PRIVATE -lmingw32)
endif()