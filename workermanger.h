#pragma once//防止重复包含头文件
#include <iostream>//包含iostream头文件
#include"worker.h"
#include"employee.h"
#include"manger.h"
#include"boss.h"
#include<fstream>
#define FILENAME "F:/C++/文件/Staff management system.txt"
using namespace std;//使用命名空间std
class WorkerManger {
public:
    WorkerManger();

    ~WorkerManger();

    //展示菜单函数
    void showMenu();

    void ExitProgram();

    int m_EmpNum;//记录职工人数

    //职工数组指针
    Worker** m_EmpArray;

    //1.添加员工
    void Add_Emp();

    //2.显示职工
    void Show_Emp();

    //保存文件
    void save();

    bool m_FileIsEmpty;//判断文件是否为空标志

    //获取文件中已存在的人数
    int getEmpNum();

    //初始化职工数组
    void initEmpArray();

    //3.删除职工
    void Del_Emp();

    //判断职工是否存在
    int isEmpExit(int id);

    //4.修改职工信息
    void Mod_Emp();

    //5.查找职工
    void Search_Emp();

    //按照姓名索引
    int* isEmpExitByName(string name);

    //6.排序
    void Sort_Emp();
};
