#include "workerManger.h"

//���캯��
WorkerManger::WorkerManger() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.�ļ������ڵ����
	if (!ifs.is_open()) {
		//cout << "��ȡ·���ļ�������!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.�ļ����ڵ����ļ�Ϊ�յ����
	char ch;
	ifs.get(ch);
	if (ifs.eof()) {
		//cout << "��ȡ·���ļ�Ϊ��!" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�ļ��������ļ���Ϊ�յ����
	this->m_EmpNum=this->getEmpNum();
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->initEmpArray();
}


//��������
WorkerManger::~WorkerManger() {

}

//�˵�
void WorkerManger::showMenu() {
	cout << "***************************************" << endl;
	cout << "*********��ӭʹ��ְ������ϵͳ!*********" << endl;
	cout << "************0.�˳��������*************" << endl;
	cout << "************1.����ְ����Ϣ*************" << endl;
	cout << "************2.��ʾְ����Ϣ*************" << endl;
	cout << "************3.ɾ����ְְ��*************" << endl;
	cout << "************4.�޸�ְ����Ϣ*************" << endl;
	cout << "************5.����ְ����Ϣ*************" << endl;
	cout << "************6.���ձ������*************" << endl;
	cout << "************7.��������ĵ�*************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

//�˳�����
void WorkerManger::ExitProgram() {
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);
}

//1.���ְ����Ϣ
void WorkerManger::Add_Emp() {
	cout << "���������ְ������:";
	int addNum = 0;
	cin >> addNum;
		if (addNum > 0) {
			//���
			//�����¿ռ�Ĵ�С
			int newSize = this->m_EmpNum + addNum;
			Worker** newArray = new Worker * [newSize];
			//���������ݵ��¿ռ�
			if (this->m_EmpNum != NULL) {
				for (int i = 0; i < this->m_EmpNum; i++) {
					newArray[i] = this->m_EmpArray[i];
				}
			}
			for (int i = 0; i < addNum; i++) {
				int id;
				string name;
				int dSelect;
				cout << "�������" << i + 1 << "��ְ�����:" << endl;
				cin >> id;
				cout << "�������" << i + 1 << "��ְ������:" << endl;
				cin >> name;
				cout << "ѡ��ְ����λ" << endl;
				cout << "1.��ְͨ��" << endl
					 << "2.����" << endl
					 << "3.�ϰ�" << endl;
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
					cout << "�������,������ѡ��ְ����λ:";
					break;
				}
				newArray[this->m_EmpNum + i] = worker;

				this->m_FileIsEmpty = false;//�ļ�Ϊ�ձ�־��Ϊflase

			}
			//�ͷ��Ͽռ�
			delete[]this->m_EmpArray;
			//��������
			this->m_EmpArray = newArray;
			//��������
			this->m_EmpNum = newSize;
			cout << "�ɹ����" << addNum << "����ְ��!" << endl;
			//���������ļ�
			this->save();
			system("pause");
			system("cls");
		}
		else {
			cout << "�������!" << endl;
		}
}


//2.��ʾְ����Ϣ
void WorkerManger::Show_Emp()
{
	if (this->m_EmpArray == NULL) {
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
		return;
	}else{
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}


//�����ļ�
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

//��ȡ�ļ���ְ������
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

//��ʼ��ְ������
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

//3.ɾ����ְְ��
void WorkerManger::Del_Emp()
{
	int id;
	cout << "������Ҫɾ��ְ���ı��:";
	cin >> id;
	if (this->isEmpExit(id) != -1) {//ְ������
		//ɾ��
		int index = isEmpExit(id);
		for (int i = 0;i<this->m_EmpNum-1;i++) {
			m_EmpArray[i] = m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
		this->save();
		cout << "�ɹ�ɾ��ְ��!" << endl;
	}else {
		cout << "�����ڸ�ְ��!" << endl;
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
	cout<<"������Ҫ�޸�ְ���ı��:";
	cin >> id;
	if (this->isEmpExit(id) != -1) {
		int index = isEmpExit(id);
		int select;
		Worker* worker = NULL;
		cout << "ѡ��ְ�����¸�λ:1.��ְͨ�� 2.���� 3.�ϰ�" << endl;
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
			cout << "�������!" << endl;
			break;
		}
		worker->m_Id = this->m_EmpArray[index]->m_Id;
		worker->m_Name = this->m_EmpArray[index]->m_Name;
		delete this->m_EmpArray[index];
		this->m_EmpArray[index] = worker;
		this->save();
		cout << "�޸ĳɹ�!" << endl;
	}
	else {
		cout << "�����ڸ�ְ��!" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManger::Search_Emp()
{
	int select=0;
	cout << "����ְ��:1.���ձ�Ų��� 2.������������";
	cin >> select;
	if (select == 2) {
		string name;
		cout << "���������ְ������:";
		cin >> name;
		int* arr=isEmpExitByName(name);
		if (arr != nullptr) {
			cout<<"�ļ�����"<<arr[0]-1 << "��ְ����" 
				<< name << "��Ա��" << endl;
			for (int i = 1; i < arr[0]; i++) {
				this->m_EmpArray[arr[i]]->showInfo();
			}
		}
		else {
			cout<<"�ļ���û�н�"<<name<<"��ְ��"<<endl;
		}
	}
	else if (select == 1) {
		//���ձ�Ų���
		int id = 0;
		cout << "���������ְ�����:";
		cin >> id;
		if (this->isEmpExit(id) != -1) {
			this->m_EmpArray[isEmpExit(id)]->showInfo();
		}
		else {
			cout << "�����ڸ�ְ��!" << endl;
		}
	}
	else {
		cout << "�������!" << endl;
	}
	system("pause");
	system("cls");
}

//������������ְ��
//����һ�����飬��һ��Ԫ�ش�����鳤�ȣ�����Ԫ�ش��ְ��������
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
	arr[0] = length;//��һ��Ԫ�ش�����鳤��
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
	cout << "1.���ձ������ 2.���ձ�Ž���" << endl;
	cin >> select;
	for (int i = 0; i < m_EmpNum; i++) {
		int minOrmax = i;

		//����
		if (select == 1) {
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (m_EmpArray[minOrmax]->m_Id > m_EmpArray[j]->m_Id) {
					minOrmax = j;
				}
			}
		}

		//����
		else if (select == 2) {
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (m_EmpArray[minOrmax]->m_Id < m_EmpArray[j]->m_Id) {
					minOrmax = j;
				}
			}
		}

		//��������
		else {
			cout << "��������!" << endl;
			return;
		}
		if (minOrmax != i) {
			Worker* temp = m_EmpArray[i];
			m_EmpArray[i] = m_EmpArray[minOrmax];
			m_EmpArray[minOrmax] = temp;
		}
	}
	this->save();
	cout << "����ɹ�!" << endl;
	system("pause");
	system("cls");
}
