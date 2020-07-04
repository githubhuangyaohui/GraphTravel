#pragma once
#include<iostream>
#include"Trourism.hpp"
using namespace std;

void list() {
	cout << "========================= 景区信息管理系统 =========================" << endl;
	cout << "1. 创建景区景点图" << endl;
	cout << "2. 查询景点信息" << endl;
	cout << "3. 旅游景点导航" << endl;
	cout << "4. 搜索最短路径" << endl;
	cout << "5. 铺设电路规划" << endl;
	cout << "6. 退出" << endl;
	cout << "请输出操作编号---->";
}
int main() {
	Trour trour;
	int sign;
	while (true) {
		system("cls");
		list();
		cin >> sign;
		switch (sign)
		{
		case 1:
			trour.CreateGraph("Vex.txt","Edge.txt");
			break;
		case 2:
			trour.GetSpotInfo();
			break;
		case 3:
			trour.TravelPath();
			break;
		case 4:
			trour.FindShortPath();
			break;
		case 5:
			trour.FindMinTree();
			break;
		case 6:
			return 0;
			break;
		default:
			cout << "输入错误，重新输入" << endl;
			break;
		}
		system("pause");
	}
	return 0;
}