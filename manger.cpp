#include "manger.h"
//���캯��
Manger::Manger(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
//��ʾ������Ϣ
void Manger::showInfo() {
	cout << "ְ�����:" << this->m_Id
		<< "\tְ������:" << this->m_Name
		<< "\t���ű��:" << this->m_DeptId
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ��:����ϰ彻��������,�·������Ա��" << endl;
}
//��ȡ��������
string Manger::getDeptName() {
	return string("����");
}