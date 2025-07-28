// main.c
#include "code_count.h"
#include "utils.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>  // Windows平台需要_conio.h头文件
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
        (void)scanf("%d", &choice);
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

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
                (void)scanf("%d", &path_choice);
                
                while ((c = getchar()) != '\n' && c != EOF);
                
                char path[1024] = ".."; // 默认路径
                
                if (path_choice == 2) 
                {
                    typeWriterPrintf("\n请输入自定义路径: ");
                    (void)fgets(path, sizeof(path), stdin);
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
                
                // 统计结束后显示感谢信息并等待退出
                typeWriterPrintf("\n感谢使用本程序。再见!");
                #ifdef _WIN32
                _getch();
                #else
                getchar();
                #endif
                return 0; // 直接退出程序
                }
            
            case 2:
                typeWriterPrintf("\n感谢使用本程序。再见!");
                #ifdef _WIN32
                // 先等待按键再退出
                _getch();
                #else
                getchar();
                #endif
                return 0;
            
            default:
                typeWriterPrintf("\n无效选择。请输入1到2之间的数字\n");
        }
    }
    
    return 0;
}
