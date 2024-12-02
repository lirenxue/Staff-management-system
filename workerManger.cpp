#include "workerManger.h"

//构造函数
WorkerManger::WorkerManger() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.文件不存在的情况
	if (!ifs.is_open()) {
		//cout << "读取路径文件不存在!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.文件存在但是文件为空的情况
	char ch;
	ifs.get(ch);
	if (ifs.eof()) {
		//cout << "读取路径文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在且文件不为空的情况
	this->m_EmpNum=this->getEmpNum();
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->initEmpArray();
}


//析构函数
WorkerManger::~WorkerManger() {

}

//菜单
void WorkerManger::showMenu() {
	cout << "***************************************" << endl;
	cout << "*********欢迎使用职工管理系统!*********" << endl;
	cout << "************0.退出管理程序*************" << endl;
	cout << "************1.增加职工信息*************" << endl;
	cout << "************2.显示职工信息*************" << endl;
	cout << "************3.删除离职职工*************" << endl;
	cout << "************4.修改职工信息*************" << endl;
	cout << "************5.查找职工信息*************" << endl;
	cout << "************6.按照编号排序*************" << endl;
	cout << "************7.清空所有文档*************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

//退出程序
void WorkerManger::ExitProgram() {
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

//1.添加职工信息
void WorkerManger::Add_Emp() {
	cout << "请输入添加职工数量:";
	int addNum = 0;
	cin >> addNum;
		if (addNum > 0) {
			//添加
			//计算新空间的大小
			int newSize = this->m_EmpNum + addNum;
			Worker** newArray = new Worker * [newSize];
			//拷贝老数据到新空间
			if (this->m_EmpNum != NULL) {
				for (int i = 0; i < this->m_EmpNum; i++) {
					newArray[i] = this->m_EmpArray[i];
				}
			}
			for (int i = 0; i < addNum; i++) {
				int id;
				string name;
				int dSelect;
				cout << "请输入第" << i + 1 << "个职工编号:" << endl;
				cin >> id;
				cout << "请输入第" << i + 1 << "个职工姓名:" << endl;
				cin >> name;
				cout << "选择职工岗位" << endl;
				cout << "1.普通职工" << endl
					 << "2.经理" << endl
					 << "3.老板" << endl;
				cin >> dSelect;
				Worker* worker = NULL;
				switch (dSelect) {
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manger(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
				default:
					cout << "输入错误,请重新选择职工岗位:";
					break;
				}
				newArray[this->m_EmpNum + i] = worker;

				this->m_FileIsEmpty = false;//文件为空标志掷为flase

			}
			//释放老空间
			delete[]this->m_EmpArray;
			//更新数据
			this->m_EmpArray = newArray;
			//更新数量
			this->m_EmpNum = newSize;
			cout << "成功添加" << addNum << "名新职工!" << endl;
			//保存数据文件
			this->save();
			system("pause");
			system("cls");
		}
		else {
			cout << "输入错误!" << endl;
		}
}


//2.显示职工信息
void WorkerManger::Show_Emp()
{
	if (this->m_EmpArray == NULL) {
		cout << "文件不存在或记录为空!" << endl;
		return;
	}else{
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}


//保存文件
void WorkerManger::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	if (ofs.is_open()) {
		for (int i = 0; i < m_EmpNum; i++) {
			ofs<<this->m_EmpArray[i]->m_Id<<" "
				<<this->m_EmpArray[i]->m_Name<<" "
				<<this->m_EmpArray[i]->m_DeptId<<endl;
		}
	}
	ofs.close();
	}

//获取文件中职工数量
int WorkerManger::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int num=0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}
	return num;
}

//初始化职工数组
void WorkerManger::initEmpArray()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		if (did == 1) {
			worker =new Employee(id, name, did);
		}
		else if (did == 2) {
			worker = new Manger(id, name, did);
		}
		else if(did==3){
			worker = new Boss(id, name, did);
		}
		m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

//3.删除离职职工
void WorkerManger::Del_Emp()
{
	int id;
	cout << "请输入要删除职工的编号:";
	cin >> id;
	if (this->isEmpExit(id) != -1) {//职工存在
		//删除
		int index = isEmpExit(id);
		for (int i = 0;i<this->m_EmpNum-1;i++) {
			m_EmpArray[i] = m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
		this->save();
		cout << "成功删除职工!" << endl;
	}else {
		cout << "不存在该职工!" << endl;
	}
	system("pause");
	system("cls");
}

int WorkerManger::isEmpExit(int id)
{
	int index = -1;
	for (int i = 0; i < m_EmpNum; i++) {
		if (m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManger::Mod_Emp()
{
	int id;
	cout<<"请输入要修改职工的编号:";
	cin >> id;
	if (this->isEmpExit(id) != -1) {
		int index = isEmpExit(id);
		int select;
		Worker* worker = NULL;
		cout << "选择职工的新岗位:1.普通职工 2.经理 3.老板" << endl;
		cin >> select;
		switch (select) {
		case 1:
			worker=new Employee(this->m_EmpArray[index]->m_Id, this->m_EmpArray[index]->m_Name, 1);
			break;
		case 2:
			worker = new Manger(this->m_EmpArray[index]->m_Id, this->m_EmpArray[index]->m_Name, 2);
			break;
		case 3:
			worker = new Boss(this->m_EmpArray[index]->m_Id, this->m_EmpArray[index]->m_Name, 3);
			break;
		default:
			cout << "输入错误!" << endl;
			break;
		}
		worker->m_Id = this->m_EmpArray[index]->m_Id;
		worker->m_Name = this->m_EmpArray[index]->m_Name;
		delete this->m_EmpArray[index];
		this->m_EmpArray[index] = worker;
		this->save();
		cout << "修改成功!" << endl;
	}
	else {
		cout << "不存在该职工!" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManger::Search_Emp()
{
	int select=0;
	cout << "查找职工:1.按照编号查找 2.按照姓名查找";
	cin >> select;
	if (select == 2) {
		string name;
		cout << "请输入查找职工姓名:";
		cin >> name;
		int* arr=isEmpExitByName(name);
		if (arr != nullptr) {
			cout<<"文件中有"<<arr[0]-1 << "个职工叫" 
				<< name << "的员工" << endl;
			for (int i = 1; i < arr[0]; i++) {
				this->m_EmpArray[arr[i]]->showInfo();
			}
		}
		else {
			cout<<"文件中没有叫"<<name<<"的职工"<<endl;
		}
	}
	else if (select == 1) {
		//按照编号查找
		int id = 0;
		cout << "请输入查找职工编号:";
		cin >> id;
		if (this->isEmpExit(id) != -1) {
			this->m_EmpArray[isEmpExit(id)]->showInfo();
		}
		else {
			cout << "不存在该职工!" << endl;
		}
	}
	else {
		cout << "输入错误!" << endl;
	}
	system("pause");
	system("cls");
}

//按照姓名查找职工
//返回一个数组，第一个元素存放数组长度，后面元素存放职工的索引
int* WorkerManger::isEmpExitByName(string name)
{
	int count=0;
	int length = 0;
	for (int i = 0; i < m_EmpNum; i++) {
		if (m_EmpArray[i]->m_Name == name) {
			count++;
		}
	}
	length=count+1;
	int* arr = new int[length];
	arr[0] = length;//第一个元素存放数组长度
	int index = 1;
	for (int i = 0; i < m_EmpNum; i++) {
		if (m_EmpArray[i]->m_Name == name) {
			arr[index] = i;
			index++;
		}
	}
	if (count == 0) {
			delete[]arr;
			return nullptr;
	}else{
		return arr;
	}
}

void WorkerManger::Sort_Emp()
{
	int select = 0;
	cout << "1.按照编号升序 2.按照编号降序" << endl;
	cin >> select;
	for (int i = 0; i < m_EmpNum; i++) {
		int minOrmax = i;

		//升序
		if (select == 1) {
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (m_EmpArray[minOrmax]->m_Id > m_EmpArray[j]->m_Id) {
					minOrmax = j;
				}
			}
		}

		//降序
		else if (select == 2) {
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (m_EmpArray[minOrmax]->m_Id < m_EmpArray[j]->m_Id) {
					minOrmax = j;
				}
			}
		}

		//输入有误
		else {
			cout << "输入有误!" << endl;
			return;
		}
		if (minOrmax != i) {
			Worker* temp = m_EmpArray[i];
			m_EmpArray[i] = m_EmpArray[minOrmax];
			m_EmpArray[minOrmax] = temp;
		}
	}
	this->save();
	cout << "排序成功!" << endl;
	system("pause");
	system("cls");
}
