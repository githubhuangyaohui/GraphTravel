#include<iostream>
#include<string>
#include<vector>
#define MAX_VEX_NUM 20
#define MAX_WIGHT 10000
using namespace std;
//顶点
struct  Vex{
	int num;	//景点编号
	string name;	//景点名字
	string desc;	//景点介绍
};
//边
struct  Edge{
	int vex1;	//顶点1
	int vex2;	//顶点2
	int weight;	//权值
};
//路径
struct Path {
	int vexs[MAX_VEX_NUM];	//保存一条路径
	Path* next;				//下一条路径
	Path() {
		memset(vexs, -1, sizeof(vexs));
		this->next = NULL;
	}
};
//创建图类
class Graph {
public:
	Graph();
	bool InsertVex(Vex vex);		//添加节点
	bool InsertEdge(Edge edge);	//添加边
	Vex GetVex(int nVex);		//查询指定顶点信息
	int FindEdge(int nVex);//查询与指定顶点相连的边
	int GetVexnum();			//获取当前节点数
	void DFSTraverse(int nVex);	//深度优先搜索
	void FindShortPath(int vexStart, int vexEnd);//查找两点间最短的路径
	void FindMinTree(); //最小生成树
private:
	void DFS(int nVex,  int nIndex, Path* pList);
	int m_aAdjMatrix[MAX_VEX_NUM][MAX_VEX_NUM];	//邻接矩阵
	Vex m_aVexs[MAX_VEX_NUM];	//顶点数组
	int m_nVexNum;	//顶点个数

	int lineNum = 0;  //规划路线数目
	bool aVisited[MAX_VEX_NUM];	//节点是否访问
	void showOneLine(Path* pList);//打印一条路线
};


void Graph::FindMinTree() {
	vector<Edge> aPath;
	aPath.clear();
	//flag[i]=0表示顶点i没有被选择
	int* flag = new int[this->m_nVexNum];
	for (int i = 0; i < this->m_nVexNum; i++)
		flag[i] = 0;
	//从顶点0开始
	flag[0] = 1;
	int m, n;
	int* prim = new int[this->m_nVexNum];
	prim[0] = 0;
	//选择总顶点数-1次，一次选择一个顶点
	for (int i = 0; i < this->m_nVexNum - 1; i++){
		int min = INT_MAX;
		//考察未选择的顶点数组中到达顶点prim[j]的距离，选出最短距离
		for (int j = 0; j <= i; j++){
			//考察未选择的顶点
			for (int k = 0; k < this->m_nVexNum; k++){
				if (flag[k] == 0 && m_aAdjMatrix[prim[j]][k] < min && m_aAdjMatrix[prim[j]][k] != 0){
					min = m_aAdjMatrix[prim[j]][k];
					m = k;
					n = prim[j];
				}
			}
		}
		flag[m] = 1;
		prim[i + 1] = m;
		Edge p;
		p.vex1 = n;
		p.vex2 = m;
		p.weight = m_aAdjMatrix[m][n];
		aPath.push_back(p);
	}
	int size = aPath.size();
	int length = 0;
	for (int i = 0; i < size; i++){
		cout << m_aVexs[aPath[i].vex1].name << "->" << m_aVexs[aPath[i].vex2].name << "\t" << aPath[i].weight << "m" << endl;
		length += aPath[i].weight;
	}
	cout << "铺设电路的总长度为：" << length << "m" << endl;
}

//查找两点间最短的路径
void Graph::FindShortPath(int vexStart, int vexEnd) {
	//邻阶矩阵把0变成最大值
	int temp[MAX_VEX_NUM][MAX_VEX_NUM];
	for (int i = 0; i < MAX_VEX_NUM; i++) {
		for (int j = 0; j < MAX_VEX_NUM; j++) {
			if (1 == j)
				temp[i][j] = 0;
			else if (this->m_aAdjMatrix[i][j] == 0)
				temp[i][j] = MAX_WIGHT;
			else
				temp[i][j] = this->m_aAdjMatrix[i][j];
		}
	}
	int dp[MAX_VEX_NUM][MAX_VEX_NUM];
	//记录路径
	int line[MAX_VEX_NUM];
	memset(line, -1, sizeof(line));
	//初始化第一行
	for (int i = 0; i < this->m_nVexNum; i++) 
		dp[0][i] = temp[vexStart][i];
	//填表
	for (int i = 0; i < this->m_nVexNum; i++) {
		if (i == vexStart) {
			for (int j = 0; j < this->m_nVexNum; j++) {
				dp[i + 1][j] = dp[i][j];
			}
			continue;
		}
		for (int j = 0; j < this->m_nVexNum; j++) {
			if (dp[i][j] <= dp[i][i] + temp[i][j])
				dp[i + 1][j] = dp[i][j];
			else
				dp[i + 1][j] = dp[i][i] + temp[i][j];
		}
	}
	int index = 0;
	int x = this->m_nVexNum;
	int y = vexEnd;
	line[0] = vexEnd;
	while (x) {
		if (x == vexStart) {
			x--;
			continue;
		}
		for (int i = 0; i < this->m_nVexNum; i++) {
			if (dp[x][y] == dp[x - 1][i] + temp[i][y]) {
				line[++index] = i;
				y = i;
				if (i == vexStart) {
					x = 1;
					break;
				}
			}
		}
		x--;
	}
	//计算输出
	int minRoute = 0;
	cout << "最短路线为:  " << this->m_aVexs[vexStart].name;
	for (int i = index - 1; i >= 0; i--) {
		minRoute += this->m_aAdjMatrix[line[i + 1]][line[i]];
		cout << "->" << this->m_aVexs[line[i]].name;
		if (line[i] == vexEnd) break;
	}
	cout << endl << "最短距离为：" << minRoute << endl;
}

//打印一条路径
void Graph::showOneLine(Path* pList) {
	cout << "路线" << this->lineNum + 1 << " ：";
	this->lineNum++;
	for (int i = 0; pList->vexs[i] != -1; i++) {
		if (i == 0)
			cout << this->m_aVexs[pList->vexs[i]].name;
		else
			cout << " -> " << this->m_aVexs[pList->vexs[i]].name;
	}
	cout << endl;
}

//深度优先搜索
void Graph::DFSTraverse(int nVex) {
	Path* pList = new Path();
	int nIndex = 0;		//记录深度
	memset(aVisited, false, sizeof(aVisited));
	this->DFS(nVex, nIndex,pList);	//遍历得到路径
}
//递归实现深度优先搜索
void Graph::DFS(int nVex, int nIndex, Path* pList) {
	aVisited[nVex] = true;	//改为已访问
	pList->vexs[nIndex++] = nVex;
	//判断是否访问完路径
	if (nIndex == this->m_nVexNum ) {
		//开辟新路径
		pList->next = new Path();
		//保存之前的路径
		for (int i = 0; i < this->m_nVexNum ; i++) {
			pList->next->vexs[i] = pList->vexs[i];
		}
		//打印路径
		this->showOneLine(pList);
		//进入新路径
		pList = pList->next;
		//返回上一层
		aVisited[nVex] = false;
	}
	else {
		for (int i = 0; i < this->m_nVexNum; i++) {
			if (i == nVex || aVisited[i])
				continue;
			if (this->m_aAdjMatrix[nVex][i] != 0) {
				this->DFS(i, nIndex, pList);
				aVisited[i] = false;
			}
		}
				nIndex--;
	}
}

//构造函数
Graph::Graph() {
	this->m_nVexNum = 0;
	for (int i = 0; i < MAX_VEX_NUM; i++)
		for (int j = 0; j < MAX_VEX_NUM; j++)
			this->m_aAdjMatrix[i][j] = 0;
}

//添加节点
bool Graph::InsertVex(Vex vex) {
	if (this->m_nVexNum == MAX_VEX_NUM)
		return false;
	else {
		this->m_aVexs[this->m_nVexNum] = vex;
		this->m_nVexNum++;
		return true;
	}
}

//添加边
bool Graph::InsertEdge(Edge edge) {
	if (edge.vex1<0 || edge.vex1 >MAX_VEX_NUM || edge.vex2 < 0 || edge.vex2>MAX_VEX_NUM)
		return false;
	else {
		this->m_aAdjMatrix[edge.vex1][edge.vex2] = edge.weight;
		this->m_aAdjMatrix[edge.vex2][edge.vex1] = edge.weight;
		return true;
	}
}

//查询指定顶点信息
Vex Graph::GetVex(int nVex) {
	return this->m_aVexs[nVex];
}

//查询与指定顶点相连的边
int Graph::FindEdge(int nVex) {
	int k = 0;
	if (nVex >= this->m_nVexNum)
		cout << "没有这个景区" << endl;
	for (int i = 0; i < this->m_nVexNum; i++) {
		if (this->m_aAdjMatrix[nVex][i] != 0) {
			cout << this->m_aVexs[nVex].name << " -> " << this->m_aVexs[i].name << "\t" << this->m_aAdjMatrix[nVex][i] << "m" << endl;
		}
	}
	return k;
}

//获取当前节点数
int Graph::GetVexnum() {
	return this->m_nVexNum;
}