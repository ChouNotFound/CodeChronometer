import os
import time
import sys

def type_writer_effect(text, delay=0.02, end=''):
    """逐字输出的打字机效果（支持自定义结束符）"""
    for char in text:
        print(char, end='', flush=True)
        time.sleep(delay)
    print(end=end)

def safe_path_concat(*paths):
    """安全的路径拼接函数"""
    return os.path.normpath(os.path.join(*paths))

def find_all_sub_dirs_for_source_files(path, total, file_list):
    """递归查找源文件"""
    try:
        for item in os.listdir(path):
            if item in ('build', 'CMakeFiles', '.git'):
                continue
            
            full_path = safe_path_concat(path, item)
            if os.path.isdir(full_path):
                find_all_sub_dirs_for_source_files(full_path, total, file_list)
            else:
                ext = os.path.splitext(item)[1].lower()
                if ext in ('.c', '.h', '.py', '.java', '.cpp', '.js', '.ts', '.md'):
                    line_count = count_lines(full_path)
                    file_list.append({'filename': item, 'line_count': line_count})
                    total[0] += line_count
    except Exception as e:
        print(f"访问目录失败：{e}", end='')

def count_lines(filename):
    """优化文件行数统计函数，使用标准库实现编码检测"""
    encodings = ['utf-8-sig', 'utf-8', 'gbk', 'latin-1', 'cp1252', 'ascii']
    
    try:
        # 尝试常见编码读取
        for enc in encodings:
            try:
                with open(filename, 'r', encoding=enc) as f:
                    lines = f.readlines()
                    return len(lines) - 1 if lines and lines[-1][-1] != '\n' else len(lines)
            except UnicodeDecodeError:
                continue
        
        # 最后尝试系统默认编码
        with open(filename, 'r') as f:
            lines = f.readlines()
            return len(lines) - 1 if lines and lines[-1][-1] != '\n' else len(lines)
            
    except FileNotFoundError:
        print(f"文件未找到：{filename}", end='')
        return 0
    except Exception as e:
        print(f"文件处理失败：{filename}，错误：{e}", end='')
        return 0

def main():
    """主函数 - 直接输出代码统计结果"""
    # 清屏并显示标题
    os.system('cls' if os.name == 'nt' else 'clear')
    type_writer_effect("=== Code Statistics Report ===\n", delay=0.05)
    
    # 初始化统计变量
    total = [0]
    file_list = []
    
    # 从上级目录开始统计
    find_all_sub_dirs_for_source_files(os.path.dirname(os.getcwd()), total, file_list)
    
    # 输出文件列表
    for file_info in file_list:
        line = f"{file_info['filename']:<30} {file_info['line_count']} lines\n"
        type_writer_effect(line, end='')
    
    # 输出总行数
    type_writer_effect("------------------------", delay=0.02)
    type_writer_effect(f"\nTotal: {total[0]} lines", delay=0.02)
    
    # 自动退出提示
    time.sleep(2)

if __name__ == '__main__':
    main()