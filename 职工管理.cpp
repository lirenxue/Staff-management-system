#include<iostream>
#include<string>

#include"workermanger.h"
#include"worker.h"
#include"employee.h"
#include"manger.h"
#include"boss.h"

using namespace std;

int main() {
	WorkerManger wm;
	int choice = 0;
	while (true) {
		wm.showMenu();
		cout << "请输入选项：";
		cin >> choice;
		switch (choice) {

		case 0://退出程序
			wm.ExitProgram();
			break;

		case 1://新增员工
			wm.Add_Emp();
			break;

		case 2://显示职工
			wm.Show_Emp();
			break;

		case 3://删除职工
			wm.Del_Emp();
			break;

		case 4://修改职工
			wm.Mod_Emp();
			break;

		case 5://查找职工
			wm.Search_Emp();
			break;

		case 6://排序职工
			wm.Sort_Emp();
			break;

		case 7://清空文件
			break;

		default:
			system("cls");
			break;
		}
	}
	return 0;
}