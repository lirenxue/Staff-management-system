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
		cout << "������ѡ�";
		cin >> choice;
		switch (choice) {

		case 0://�˳�����
			wm.ExitProgram();
			break;

		case 1://����Ա��
			wm.Add_Emp();
			break;

		case 2://��ʾְ��
			wm.Show_Emp();
			break;

		case 3://ɾ��ְ��
			wm.Del_Emp();
			break;

		case 4://�޸�ְ��
			wm.Mod_Emp();
			break;

		case 5://����ְ��
			wm.Search_Emp();
			break;

		case 6://����ְ��
			wm.Sort_Emp();
			break;

		case 7://����ļ�
			break;

		default:
			system("cls");
			break;
		}
	}
	return 0;
}