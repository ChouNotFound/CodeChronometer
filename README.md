# 代码统计系统 (CodeChronometer)

## 项目简介
本项目是一个高效、跨平台的代码行数统计工具，采用C语言实现核心功能，提供多种编程语言支持和独特的打字机动画输出效果。适用于程序员、开发团队和项目管理者进行代码规模评估。

## 核心功能
- ✅ 递归统计目录下的代码文件（支持C/C++/Python/Java/JavaScript/TypeScript/Markdown）
- 🌍 完全跨平台支持（Windows/Linux）
- 🎮 独特的打字机动画风格交互式输出
- 🚫 智能过滤构建目录和CMake相关文件
- 📁 支持两种路径选择模式：
  - 默认使用当前目录
  - 手动输入自定义路径
- 📄 自动生成统计报告并保存至独立目录
- 🧠 支持多语言代码分析（自动识别文件类型）
- 📈 可视化统计结果展示（进度条+详细统计报告）

## 技术架构
### 技术选型
- **编程语言**：C11标准（保证性能）
- **构建工具**：CMake 3.10+（推荐3.15+）
- **编译器支持**：MSVC/GCC/Clang
- **脚本语言**：Python（辅助脚本）

### 系统架构
```
├── include/        # 模块化头文件
│   ├── code_count.h
│   └── typewriter.h
├── scripts/        # 辅助脚本
│   └── count.py
├── src/            # 核心源代码
│   ├── code_count.c  # 代码统计核心算法
│   ├── main.c        # 程序入口及菜单逻辑
│   └── typewriter.c  # 动画输出引擎
└── README.md       # 项目说明文件
```

## 开发环境配置
### Windows环境（推荐使用Chocolatey包管理器）
```powershell
choco install cmake
gsudo choco install mingw -params "AddToPath"
```

### Linux环境（Ubuntu/Debian）
```bash
sudo apt-get update
sudo apt-get install build-essential cmake
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
运行生成的可执行文件后，将进入交互式菜单：
1. 📊 运行代码统计
2. 📁 生成统计报告
3. 🚪 退出程序

程序执行完成后会显示"Press any key to return to menu..."提示，支持任意键返回主菜单。

## 技术规范
- **代码规范**：遵循C11标准，启用-Wall -Wextra警告选项
- **跨平台**：支持UTF-8编码输出（Windows使用`_setmode`，Linux使用`setlocale`）
- **性能要求**：高效处理大目录和大文件
- **安全要求**：无特殊安全需求

## 已知限制
- 默认统计当前目录的代码文件（可通过参数扩展）
- Windows系统需要管理员权限运行以避免输出权限问题
- 默认仅支持特定文件类型（可扩展）

## 许可证
MIT License

## 贡献指南
欢迎提交PR或Issue来帮助完善项目功能！贡献时请遵循以下规范：
1. 保持代码可读性，避免使用三元运算符
2. 使用空行分隔逻辑段落
3. 添加必要的注释说明关键操作
4. 遵循函数优化与重构规范
5. 保持文档与代码同步更新