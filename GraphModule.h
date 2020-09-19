#pragma once
#include <stdio.h>
using namespace std;
/*
*深度优先搜索
*/
#define VRType int                          //表示顶点之间的关系的变量类型
#define VertexType int                      //图中顶点的数据类型
#define InfoType char 

const int MAX_VERtEX_NUM = 20;                 //顶点的最大个数
typedef enum { False, True }BOOL;               //定义BOOL型常量（练习而已：可以直接使用关键字bool）
BOOL visited[MAX_VERtEX_NUM];               //设置全局数组，记录标记顶点是否被访问过

typedef struct {
	VRType adj;                             //对于无权图，用 1 或 0 表示是否相邻；对于带权图，直接为权值。
	InfoType * info;                        //弧或边额外含有的信息指针
}ArcCell, AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERtEX_NUM];        //存储图中顶点数据
	AdjMatrix arcs;                         //二维数组，记录顶点之间的关系
	int vexnum, arcnum;                      //记录图的顶点数和弧（边）数
}MGraph;
//根据顶点本身数据，判断出顶点在二维数组中的位置
int LocateVex(MGraph * G, VertexType v) {
	int i = 0;
	//遍历一维数组，找到变量v
	for (; i<G->vexnum; i++) {
		if (G->vexs[i] == v) {
			break;
		}
	}
	//如果找不到，输出提示语句，返回-1
	if (i>G->vexnum) {
		printf("no such vertex.\n");
		return -1;
	}
	return i;
}
//构造无向图/网
void CreateDN(MGraph *G) {
	printf("输入顶点数和边数（顶点数,边数）：");
	scanf_s("%d,%d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i<G->vexnum; i++) {
		printf("记录顶点数据(用数字代替)：");
		scanf_s("%d", &(G->vexs[i]));
		getchar();
	}
	for (int i = 0; i<G->vexnum; i++) {
		for (int j = 0; j<G->vexnum; j++) {
			G->arcs[i][j].adj = 0;
			G->arcs[i][j].info = NULL;
		}
	}
	for (int i = 0; i<G->arcnum; i++) {
		int v1, v2;
		printf("设置顶点邻接信息（矩阵下标表示):");
		scanf_s("%d,%d", &v1, &v2); getchar();
		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		if (m == -1 || n == -1) {
			printf("no this vertex\n");
			return;
		}
		G->arcs[n][m].adj = 1;
		G->arcs[m][n].adj = 1;//无向图的二阶矩阵沿主对角线对称
		
		
	}
	//矩阵表示法输出
	cout << "图的矩阵表示：" << endl;
	for (int i = 0; i < G->vexnum; ++i) {
		for (int j = 0; j < G->vexnum; ++j) {
			cout << G->arcs[i][j].adj << "\t";

		}
		cout << "\n";
	}
}
//构造有向图/网
void CreateDir(MGraph *G) {
	printf("输入顶点数和边数（顶点数,边数）：");
	scanf_s("%d,%d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i<G->vexnum; i++) {
		printf("记录顶点数据(用数字代替)：");
		scanf_s("%d", &(G->vexs[i]));
		getchar();
	}
	for (int i = 0; i<G->vexnum; i++) {
		for (int j = 0; j<G->vexnum; j++) {
			G->arcs[i][j].adj = 0;
			G->arcs[i][j].info = NULL;
		}
	}
	for (int i = 0; i<G->arcnum; i++) {
		int v1, v2;
		printf("设置顶点邻接信息（矩阵下标表示）:");
		scanf_s("%d,%d", &v1, &v2); getchar();
		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		if (m == -1 || n == -1) {
			printf("no this vertex\n");
			return;
		}
		G->arcs[n][m].adj = 1;

		//G->arcs[m][n].adj = 1;//无向图的二阶矩阵沿主对角线对称
	}
	//矩阵表示法输出
	cout << "图的矩阵表示：" << endl;
	for (int i = 0; i < G->vexnum; ++i) {
		for (int j = 0; j < G->vexnum; ++j) {
			cout << G->arcs[i][j].adj << "\t";

		}
		cout << "\n";
	}
}

void TopologicalSort(MGraph* G) 
{
	int i, j, k = 0, m;
	char vexs[MAX_VERtEX_NUM];

	while (k < G->vexnum) {
		//1.找没有入度的顶点,存入数组vexs中
		for (i = 0; i<G->vexnum; i++) {
			for (j = 0; j<G->vexnum; j++) {
				if (G->arcs[j][i].adj != 0)//有入度
					break;
			}
			if (j == G->vexnum) {
				//检查G->vexs[i]是否已经遍历
				for (m = 0; m<k; m++)
					if (vexs[m] == G->vexs[i])
						break;
				if (m == k) {
					vexs[k++] = G->vexs[i];
					break;
				}
			}
		}
		//2.没有入度为0的顶点
		if (i == G->vexnum) {
			printf("存在回路!\n");
			return;
		}
		//3.删除这个顶点的出度
		for (j = 0; j<G->vexnum; j++)
			G->arcs[i][j].adj = 0;
	}
	//输出排序后的结果
	printf("拓扑排序结果：\n");
	for (i = 0; i<k; i++)
		printf("%-3d", vexs[i]);
	printf("\n");
}
///////////////////////////////////////////////////////
int FirstAdjVex(MGraph G, int v)
{
	//查找与数组下标为v的顶点之间有边的顶点，返回它在数组中的下标
	for (int i = 0; i<G.vexnum; i++) {
		if (G.arcs[v][i].adj) {
			return i;
		}
	}
	return -1;
}
int NextAdjVex(MGraph G, int v, int w)
{
	//从前一个访问位置w的下一个位置开始，查找之间有边的顶点
	for (int i = w + 1; i<G.vexnum; i++) {
		if (G.arcs[v][i].adj) {
			return i;
		}
	}
	return -1;
}
void visitVex(MGraph G, int v) {
	printf("%d ", G.vexs[v]);
}
void DFS(MGraph G, int v) {
	visited[v] = True;//标记为True
	visitVex(G, v); //访问第v 个顶点
					//从该顶点的第一个边开始，一直到最后一个边，对处于边另一端的顶点调用DFS函数
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		//如果该顶点的标记位False，证明未被访问，调用深度优先搜索函数
		if (!visited[w]) {
			DFS(G, w);
		}
	}
}
//深度优先搜索
void DFSTraverse(MGraph G) {//
	printf("深度优先遍历序列：");
	int v;
	//将用做标记的visit数组初始化为False
	for (v = 0; v < G.vexnum; ++v) {
		visited[v] = False;
	}
	//对于每个标记为False的顶点调用深度优先搜索函数
	for (v = 0; v < G.vexnum; v++) {
		//如果该顶点的标记位为False，则调用深度优先搜索函数
		if (!visited[v]) {
			DFS(G, v);
		}
	}
}