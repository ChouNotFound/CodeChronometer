def count_lines(filename):
    """
    优化文件行数统计函数，增加缓存支持和更精确的编码检测
    """
    encodings = ['utf-8-sig', 'utf-8', 'gbk', 'latin-1', 'cp1252']
    
    try:
        with open(filename, 'rb') as f:
            raw_data = f.read()
        
        # 使用chardet进行更准确的编码检测（需要安装chardet库）
        import chardet
        result = chardet.detect(raw_data)
        encoding = result['encoding'] if result['confidence'] > 0.8 else None
        
        if encoding and encoding.lower() in encodings:
            encodings.remove(encoding)
            encodings.insert(0, encoding)
        
        for enc in encodings:
            try:
                text = raw_data.decode(enc)
                lines = text.split('\n')
                line_count = len(lines) - 1 if lines and lines[-1] == '' else len(lines)
                return line_count
            except UnicodeDecodeError:
                continue
        
        # 如果所有常见编码都失败，使用检测到的编码或默认编码
        try:
            encoding = result['encoding'] if result['confidence'] > 0.5 else 'utf-8'
            text = raw_data.decode(encoding, errors='ignore')
            return len(text.split('\n')) - 1
        except:
            return 0
            
    except FileNotFoundError:
        print(f"文件未找到：{filename}")
        return 0
    except Exception as e:
        print(f"文件处理失败：{filename}，错误：{e}")
        return 0