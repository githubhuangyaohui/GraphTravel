#pragma once
#include"Graph.hpp"
#include<string>
#include<fstream>
class Trour {
public:
	void CreateGraph(string PathVex, string PathEdge);		//创建图
	void GetSpotInfo();		//查询指定景点信息，显示到相邻景点的距离
	void TravelPath();		//旅游景点导航
	void FindShortPath();	//查找最短路径
	void FindMinTree();		//铺设电缆
private:
	Graph grp;
};
//铺设电缆
void Trour::FindMinTree() {
	cout << "---------------------------- 铺设电缆规划 ------------------------------" << endl;
	cout << "在以下两个景点之间铺设电路：" << endl;
	this->grp.FindMinTree();
}
//查找最短路径
void Trour::FindShortPath() {
	cout << "---------------------------- 搜索最短路径 ------------------------------" << endl;
	for (int i = 0; i < this->grp.GetVexnum(); i++) {
		cout << this->grp.GetVex(i).num << "\t" << this->grp.GetVex(i).name << endl;
	}
	int startVex;
	int endVex;
	cout << "输入起点编号：";
	cin >> startVex;
	cout << "输入终点编号：";
	cin >> endVex;
	this->grp.FindShortPath(startVex,endVex);
}

//旅游景点导航
void Trour::TravelPath() {
	cout << "---------------------------- 旅游景点导航 ------------------------------" << endl;
	for (int i = 0; i < this->grp.GetVexnum(); i++) {
		cout << this->grp.GetVex(i).num << "\t" << this->grp.GetVex(i).name << endl;
	}
	int number;
	cout << "输入起始景点编号：";
	cin >> number;
	this->grp.DFSTraverse(number);
}
//创建图
void Trour::CreateGraph(string PathVex,string PathEdge) {
	Vex tempV;
	Edge tempE;
	//读取节点
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
	//读取边
	ifstream inEdge(PathEdge);
	while (!inEdge.eof()) {
		inEdge >> tempE.vex1;
		inEdge >> tempE.vex2;
		inEdge >> tempE.weight;
		this->grp.InsertEdge(tempE);
	}
	inEdge.close();
	cout << "读取成功" << endl;
}
//查询指定景点信息，显示到相邻景点的距离
void Trour::GetSpotInfo() {
	for (int i = 0; i < this->grp.GetVexnum(); i++) {
		cout << this->grp.GetVex(i).num << "\t" << this->grp.GetVex(i).name << endl;
	}
	int number;
	cout << "输入想要查询的景点编号：";
	cin >> number;
	cout << "---------------------------- 周边景区 ------------------------------" << endl;
	this->grp.FindEdge(number);
}