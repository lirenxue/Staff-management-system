#include "manger.h"
//构造函数
Manger::Manger(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
//显示个人信息
void Manger::showInfo() {
	cout << "职工编号:" << this->m_Id
		<< "\t职工姓名:" << this->m_Name
		<< "\t部门编号:" << this->m_DeptId
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责:完成老板交给的任务,下发任务给员工" << endl;
}
//获取部门名称
string Manger::getDeptName() {
	return string("经理");
}