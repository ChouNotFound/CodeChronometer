# 代码统计系统

## 项目简介
本项目是一个高效、跨平台的代码行数统计工具，采用C语言实现核心功能，提供多种编程语言支持和独特的打字机动画输出效果。

## 核心功能
- ✅ 递归统计目录下的代码文件
- 🌍 支持C/C++/Python/Java/JavaScript/TypeScript/Markdown等主流语言
- 🖥️ 跨平台运行（Windows/Linux）
- 🎮 打字机动画风格的交互式输出效果
- 🚫 自动跳过构建目录和CMake相关文件

## 技术架构
- **编程语言**：C11标准
- **构建工具**：CMake 3.10+
- **编译器支持**：MSVC/GCC/Clang
- **核心模块**：
  - `code_count.c`：代码统计核心算法
  - `typewriter.c`：动画输出引擎
  - `main.c`：程序入口

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

## 开发环境配置
```powershell
# Windows环境配置示例
choco install cmake
choco install mingw
```

## 构建指南
```bash
# 创建并进入构建目录
cd code
cmake -B build -S .

# 执行构建
cmake --build build
```

## 使用说明
运行生成的可执行文件后，选择功能选项即可自动统计代码行数。支持以下操作：
1. 📊 运行代码统计
2. 🚪 退出程序

## 已知限制
- 默认统计当前目录的代码文件（可通过参数扩展）
- 支持的文件类型：C/C++/Python/Java/JavaScript/TypeScript/Markdown
- Windows系统需要管理员权限运行以避免输出权限问题

## 许可证
MIT License

## 贡献指南
欢迎提交PR或Issue来帮助完善项目功能！