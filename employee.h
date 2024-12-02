//普通员工头文件
#pragma once
#include<iostream>
#include"worker.h"
class Employee :public Worker {
public:
	Employee(int id, string name, int did);
	virtual void showInfo();
	virtual string getDeptName();
};
