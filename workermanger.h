#pragma once//��ֹ�ظ�����ͷ�ļ�
#include <iostream>//����iostreamͷ�ļ�
#include"worker.h"
#include"employee.h"
#include"manger.h"
#include"boss.h"
#include<fstream>
#define FILENAME "F:/C++/�ļ�/Staff management system.txt"
using namespace std;//ʹ�������ռ�std
class WorkerManger {
public:
    WorkerManger();

    ~WorkerManger();

    //չʾ�˵�����
    void showMenu();

    void ExitProgram();

    int m_EmpNum;//��¼ְ������

    //ְ������ָ��
    Worker** m_EmpArray;

    //1.���Ա��
    void Add_Emp();

    //2.��ʾְ��
    void Show_Emp();

    //�����ļ�
    void save();

    bool m_FileIsEmpty;//�ж��ļ��Ƿ�Ϊ�ձ�־

    //��ȡ�ļ����Ѵ��ڵ�����
    int getEmpNum();

    //��ʼ��ְ������
    void initEmpArray();

    //3.ɾ��ְ��
    void Del_Emp();

    //�ж�ְ���Ƿ����
    int isEmpExit(int id);

    //4.�޸�ְ����Ϣ
    void Mod_Emp();

    //5.����ְ��
    void Search_Emp();

    //������������
    int* isEmpExitByName(string name);

    //6.����
    void Sort_Emp();
};
