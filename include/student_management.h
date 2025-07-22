// student_management.h

#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100  // 最大学生数量

// 定义学生结构体
typedef struct {
    char name[50];  // 可存储50个中文字符
    int id;
    float score;
} Student;

// 学生数组，用于存储学生信息
extern Student students[MAX_STUDENTS];
extern int student_count;  // 当前学生数量

// 函数声明
void add_student();
void display_students();
Student* find_student(int id);
float calculate_average_score();

// 启动学生管理系统的函数声明
void run_student_management();

#endif // STUDENT_MANAGEMENT_H