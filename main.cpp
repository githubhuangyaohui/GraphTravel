#pragma once
#include<iostream>
#include"Trourism.hpp"
using namespace std;

void list() {
	cout << "========================= ������Ϣ����ϵͳ =========================" << endl;
	cout << "1. ������������ͼ" << endl;
	cout << "2. ��ѯ������Ϣ" << endl;
	cout << "3. ���ξ��㵼��" << endl;
	cout << "4. �������·��" << endl;
	cout << "5. �����·�滮" << endl;
	cout << "6. �˳�" << endl;
	cout << "������������---->";
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
			cout << "���������������" << endl;
			break;
		}
		system("pause");
	}
	return 0;
}