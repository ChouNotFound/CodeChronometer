# 代码统计系统

## 项目简介
本项目是一个跨平台的代码行数统计工具，支持多种编程语言文件的代码统计功能，包含打字机风格的动画输出效果。

## 功能特点
- 支持递归统计目录下的代码文件
- 支持多种编程语言（C/C++/Python/Java/JavaScript/TypeScript/Markdown等）
- 跨平台支持（Windows/Linux）
- 带打字机动画效果的输出显示
- 自动跳过构建目录和CMake相关文件

## 目录结构
```
├── include/        # 头文件目录
│   ├── code_count.h
│   └── typewriter.h
├── scripts/        # 脚本文件
│   └── count.py
├── src/            # 源代码目录
│   ├── code_count.c
│   ├── main.c
│   └── typewriter.c
└── README.md       # 项目说明文件
```

## 安装说明
1. 安装CMake（版本3.15+）
2. 安装C/C++编译器（MSVC/GCC/Clang）
3. 创建build目录并执行CMake构建
```
cd code
cmake -B build -S .
cmake --build build
```

## 使用方法
运行生成的可执行文件，选择功能选项即可自动统计代码行数，支持以下功能：
1. 运行代码统计
2. 退出程序

## 注意事项
- 默认统计当前目录的代码文件
- 支持的文件类型：C/C++/Python/Java/JavaScript/TypeScript/Markdown
- 自动跳过build目录和CMake相关文件
- Windows系统需要管理员权限运行以避免输出权限问题

## 许可证
MIT License