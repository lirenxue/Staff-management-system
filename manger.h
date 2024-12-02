#pragma once
#include <iostream>
using namespace std;
#include"worker.h"
class Manger :public Worker {
public:
	Manger(int id, string name, int did);
	virtual void showInfo();
	virtual string getDeptName();
};

