import os

def count_lines(filename):
    """
    统计文件的行数，尝试使用常见编码格式打开文件，避免解码错误
    
    参数:
        filename (str): 需要统计的文件路径
        
    返回:
        int: 文件的行数，如果文件无法读取或解码失败则返回0
    """
    # 常见编码格式列表，尝试顺序很重要
    encodings = ['utf-8-sig', 'utf-8', 'gbk', 'latin-1']
    
    try:
        # 以二进制模式读取文件内容
        with open(filename, 'rb') as f:
            raw_data = f.read()
        
        # 尝试使用不同的编码格式解码文件内容
        for encoding in encodings:
            try:
                # 解码并按换行符分割
                text = raw_data.decode(encoding)
                lines = text.split('\n')
                
                # 如果最后一个元素为空字符串，说明以换行结束，不额外加行
                if lines and lines[-1] == '':
                    line_count = len(lines) - 1
                else:
                    line_count = len(lines)
                
                return line_count
                
            except UnicodeDecodeError:
                continue  # 当前编码不匹配，尝试下一个编码
        
        # 所有编码都失败的情况
        print(f"无法识别编码格式：{filename}")
        return 0
        
    except FileNotFoundError:
        print(f"文件未找到：{filename}")
        return 0
    except Exception as e:
        print(f"文件处理失败：{filename}，错误：{e}")
        return 0

def find_all_c_files(path, total):
    """
    查找指定目录下的所有 .c 文件，并统计其行数
    
    参数:
        path (str): 要搜索的目录路径
        total (list): 用于保存总行数的列表（使用列表模拟指针）
    """
    try:
        # 遍历目录中的文件
        for file in os.listdir(path):
            if file.endswith(".c"):
                full_path = os.path.join(path, file)
                lines = count_lines(full_path)
                total[0] += lines
                print(f"{full_path} - {lines} 行")
    except Exception as e:
        print(f"无法访问目录：{path}，错误：{e}")

def find_all_sub_dirs(path, total):
    """
    递归遍历所有子目录并查找 .c 文件
    
    参数:
        path (str): 要搜索的目录路径
        total (list): 用于保存总行数的列表（使用列表模拟指针）
    """
    try:
        # 使用os.scandir提高效率
        for entry in os.scandir(path):
            if entry.is_dir():
                sub_dir_path = entry.path
                find_all_c_files(sub_dir_path, total)
                find_all_sub_dirs(sub_dir_path, total)
    except Exception as e:
        print(f"无法访问目录：{path}，错误：{e}")

def main():
    """
    主函数，程序执行入口
    """
    path = "."  # 默认统计当前目录
    total = [0]  # 使用列表模拟指针，以便在函数中修改值
    
    print("统计中...")
    
    # 查找当前目录下的 .c 文件
    find_all_c_files(path, total)
    
    # 递归查找子目录中的 .c 文件
    find_all_sub_dirs(path, total)
    
    print(f"目前总共写了 {total[0]} 行代码。")

if __name__ == "__main__":
    main()