#include "code_count.h"
#include "utils.h"
#include <stdio.h>
#include <conio.h>
#include <direct.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main() 
{
    SetConsoleOutputCP(CP_UTF8);
    while (1) 
    {
        typeWriterPrintf("\n=== 代码统计系统 ===\n");
        typeWriterPrintf("1. 执行代码统计\n");
        typeWriterPrintf("2. 退出\n");
        typeWriterPrintf("请输入你的选择 (1-2): ");
        
        int choice;
        // 使用输入验证函数改进用户交互
        while (!get_valid_input(&choice) || (choice < 1 || choice > 2)) 
        {
            typeWriterPrintf("\n输入无效，请输入1或2：");
        }

        switch (choice) 
        {
            case 1:
                {
                // 添加路径选择逻辑
                typeWriterPrintf("\n请选择路径选项:\n");
                typeWriterPrintf("1. 当前目录\n");
                typeWriterPrintf("2. 自定义路径\n");
                typeWriterPrintf("请输入你的选择 (1-2): ");
                
                int path_choice;
                // 使用输入验证函数改进用户交互
                while (!get_valid_input(&path_choice) || (path_choice < 1 || path_choice > 2)) 
                {
                    typeWriterPrintf("\n输入无效，请输入1或2：");
                }
                
                char path[1024]; // 路径缓冲区
                strcpy(path, ".."); // 默认路径
                
                if (path_choice == 2) 
                {
                    typeWriterPrintf("\n请输入自定义路径: ");
                    (void)fgets(path, sizeof(path), stdin);
                    // 移除末尾换行符
                    path[strcspn(path, "\n")] = '\0';
                }
                
                typeWriterPrintf("\n是否生成报告文件? (y/n): ");
                char report_choice;
                (void)scanf(" %c", &report_choice);
                if (report_choice == 'y' || report_choice == 'Y') 
                {
                    generate_report();
                }
                
                // 执行代码统计，使用选择的路径
                run_code_count(path);
                }
            
            case 2:
                typeWriterPrintf("\n感谢使用本程序，再见!");
                return 0;
        }
    }
}