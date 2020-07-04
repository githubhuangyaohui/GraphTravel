#pragma once
#include"Graph.hpp"
#include<string>
#include<fstream>
class Trour {
public:
	void CreateGraph(string PathVex, string PathEdge);		//����ͼ
	void GetSpotInfo();		//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
	void TravelPath();		//���ξ��㵼��
	void FindShortPath();	//�������·��
	void FindMinTree();		//�������
private:
	Graph grp;
};
//�������
void Trour::FindMinTree() {
	cout << "---------------------------- ������¹滮 ------------------------------" << endl;
	cout << "��������������֮�������·��" << endl;
	this->grp.FindMinTree();
}
//�������·��
void Trour::FindShortPath() {
	cout << "---------------------------- �������·�� ------------------------------" << endl;
	for (int i = 0; i < this->grp.GetVexnum(); i++) {
		cout << this->grp.GetVex(i).num << "\t" << this->grp.GetVex(i).name << endl;
	}
	int startVex;
	int endVex;
	cout << "��������ţ�";
	cin >> startVex;
	cout << "�����յ��ţ�";
	cin >> endVex;
	this->grp.FindShortPath(startVex,endVex);
}

//���ξ��㵼��
void Trour::TravelPath() {
	cout << "---------------------------- ���ξ��㵼�� ------------------------------" << endl;
	for (int i = 0; i < this->grp.GetVexnum(); i++) {
		cout << this->grp.GetVex(i).num << "\t" << this->grp.GetVex(i).name << endl;
	}
	int number;
	cout << "������ʼ�����ţ�";
	cin >> number;
	this->grp.DFSTraverse(number);
}
//����ͼ
void Trour::CreateGraph(string PathVex,string PathEdge) {
	Vex tempV;
	Edge tempE;
	//��ȡ�ڵ�
	ifstream inVex(PathVex);
	int numVex;
	inVex >> numVex;
	for (int i = 0; i < numVex; i++) {
		inVex >> tempV.num;
		inVex >> tempV.name;
		inVex >> tempV.desc;
		this->grp.InsertVex(tempV);
	}
	inVex.close();
	//��ȡ��
	ifstream inEdge(PathEdge);
	while (!inEdge.eof()) {
		inEdge >> tempE.vex1;
		inEdge >> tempE.vex2;
		inEdge >> tempE.weight;
		this->grp.InsertEdge(tempE);
	}
	inEdge.close();
	cout << "��ȡ�ɹ�" << endl;
}
//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
void Trour::GetSpotInfo() {
	for (int i = 0; i < this->grp.GetVexnum(); i++) {
		cout << this->grp.GetVex(i).num << "\t" << this->grp.GetVex(i).name << endl;
	}
	int number;
	cout << "������Ҫ��ѯ�ľ����ţ�";
	cin >> number;
	cout << "---------------------------- �ܱ߾��� ------------------------------" << endl;
	this->grp.FindEdge(number);
}