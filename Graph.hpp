#include<iostream>
#include<string>
#include<vector>
#define MAX_VEX_NUM 20
#define MAX_WIGHT 10000
using namespace std;
//����
struct  Vex{
	int num;	//������
	string name;	//��������
	string desc;	//�������
};
//��
struct  Edge{
	int vex1;	//����1
	int vex2;	//����2
	int weight;	//Ȩֵ
};
//·��
struct Path {
	int vexs[MAX_VEX_NUM];	//����һ��·��
	Path* next;				//��һ��·��
	Path() {
		memset(vexs, -1, sizeof(vexs));
		this->next = NULL;
	}
};
//����ͼ��
class Graph {
public:
	Graph();
	bool InsertVex(Vex vex);		//��ӽڵ�
	bool InsertEdge(Edge edge);	//��ӱ�
	Vex GetVex(int nVex);		//��ѯָ��������Ϣ
	int FindEdge(int nVex);//��ѯ��ָ�����������ı�
	int GetVexnum();			//��ȡ��ǰ�ڵ���
	void DFSTraverse(int nVex);	//�����������
	void FindShortPath(int vexStart, int vexEnd);//�����������̵�·��
	void FindMinTree(); //��С������
private:
	void DFS(int nVex,  int nIndex, Path* pList);
	int m_aAdjMatrix[MAX_VEX_NUM][MAX_VEX_NUM];	//�ڽӾ���
	Vex m_aVexs[MAX_VEX_NUM];	//��������
	int m_nVexNum;	//�������

	int lineNum = 0;  //�滮·����Ŀ
	bool aVisited[MAX_VEX_NUM];	//�ڵ��Ƿ����
	void showOneLine(Path* pList);//��ӡһ��·��
};


void Graph::FindMinTree() {
	vector<Edge> aPath;
	aPath.clear();
	//flag[i]=0��ʾ����iû�б�ѡ��
	int* flag = new int[this->m_nVexNum];
	for (int i = 0; i < this->m_nVexNum; i++)
		flag[i] = 0;
	//�Ӷ���0��ʼ
	flag[0] = 1;
	int m, n;
	int* prim = new int[this->m_nVexNum];
	prim[0] = 0;
	//ѡ���ܶ�����-1�Σ�һ��ѡ��һ������
	for (int i = 0; i < this->m_nVexNum - 1; i++){
		int min = INT_MAX;
		//����δѡ��Ķ��������е��ﶥ��prim[j]�ľ��룬ѡ����̾���
		for (int j = 0; j <= i; j++){
			//����δѡ��Ķ���
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
	cout << "�����·���ܳ���Ϊ��" << length << "m" << endl;
}

//�����������̵�·��
void Graph::FindShortPath(int vexStart, int vexEnd) {
	//�ڽ׾����0������ֵ
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
	//��¼·��
	int line[MAX_VEX_NUM];
	memset(line, -1, sizeof(line));
	//��ʼ����һ��
	for (int i = 0; i < this->m_nVexNum; i++) 
		dp[0][i] = temp[vexStart][i];
	//���
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
	//�������
	int minRoute = 0;
	cout << "���·��Ϊ:  " << this->m_aVexs[vexStart].name;
	for (int i = index - 1; i >= 0; i--) {
		minRoute += this->m_aAdjMatrix[line[i + 1]][line[i]];
		cout << "->" << this->m_aVexs[line[i]].name;
		if (line[i] == vexEnd) break;
	}
	cout << endl << "��̾���Ϊ��" << minRoute << endl;
}

//��ӡһ��·��
void Graph::showOneLine(Path* pList) {
	cout << "·��" << this->lineNum + 1 << " ��";
	this->lineNum++;
	for (int i = 0; pList->vexs[i] != -1; i++) {
		if (i == 0)
			cout << this->m_aVexs[pList->vexs[i]].name;
		else
			cout << " -> " << this->m_aVexs[pList->vexs[i]].name;
	}
	cout << endl;
}

//�����������
void Graph::DFSTraverse(int nVex) {
	Path* pList = new Path();
	int nIndex = 0;		//��¼���
	memset(aVisited, false, sizeof(aVisited));
	this->DFS(nVex, nIndex,pList);	//�����õ�·��
}
//�ݹ�ʵ�������������
void Graph::DFS(int nVex, int nIndex, Path* pList) {
	aVisited[nVex] = true;	//��Ϊ�ѷ���
	pList->vexs[nIndex++] = nVex;
	//�ж��Ƿ������·��
	if (nIndex == this->m_nVexNum ) {
		//������·��
		pList->next = new Path();
		//����֮ǰ��·��
		for (int i = 0; i < this->m_nVexNum ; i++) {
			pList->next->vexs[i] = pList->vexs[i];
		}
		//��ӡ·��
		this->showOneLine(pList);
		//������·��
		pList = pList->next;
		//������һ��
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

//���캯��
Graph::Graph() {
	this->m_nVexNum = 0;
	for (int i = 0; i < MAX_VEX_NUM; i++)
		for (int j = 0; j < MAX_VEX_NUM; j++)
			this->m_aAdjMatrix[i][j] = 0;
}

//��ӽڵ�
bool Graph::InsertVex(Vex vex) {
	if (this->m_nVexNum == MAX_VEX_NUM)
		return false;
	else {
		this->m_aVexs[this->m_nVexNum] = vex;
		this->m_nVexNum++;
		return true;
	}
}

//��ӱ�
bool Graph::InsertEdge(Edge edge) {
	if (edge.vex1<0 || edge.vex1 >MAX_VEX_NUM || edge.vex2 < 0 || edge.vex2>MAX_VEX_NUM)
		return false;
	else {
		this->m_aAdjMatrix[edge.vex1][edge.vex2] = edge.weight;
		this->m_aAdjMatrix[edge.vex2][edge.vex1] = edge.weight;
		return true;
	}
}

//��ѯָ��������Ϣ
Vex Graph::GetVex(int nVex) {
	return this->m_aVexs[nVex];
}

//��ѯ��ָ�����������ı�
int Graph::FindEdge(int nVex) {
	int k = 0;
	if (nVex >= this->m_nVexNum)
		cout << "û���������" << endl;
	for (int i = 0; i < this->m_nVexNum; i++) {
		if (this->m_aAdjMatrix[nVex][i] != 0) {
			cout << this->m_aVexs[nVex].name << " -> " << this->m_aVexs[i].name << "\t" << this->m_aAdjMatrix[nVex][i] << "m" << endl;
		}
	}
	return k;
}

//��ȡ��ǰ�ڵ���
int Graph::GetVexnum() {
	return this->m_nVexNum;
}