#pragma once
#include <stdio.h>
using namespace std;
/*
*�����������
*/
#define VRType int                          //��ʾ����֮��Ĺ�ϵ�ı�������
#define VertexType int                      //ͼ�ж������������
#define InfoType char 

const int MAX_VERtEX_NUM = 20;                 //�����������
typedef enum { False, True }BOOL;               //����BOOL�ͳ�������ϰ���ѣ�����ֱ��ʹ�ùؼ���bool��
BOOL visited[MAX_VERtEX_NUM];               //����ȫ�����飬��¼��Ƕ����Ƿ񱻷��ʹ�

typedef struct {
	VRType adj;                             //������Ȩͼ���� 1 �� 0 ��ʾ�Ƿ����ڣ����ڴ�Ȩͼ��ֱ��ΪȨֵ��
	InfoType * info;                        //����߶��⺬�е���Ϣָ��
}ArcCell, AdjMatrix[MAX_VERtEX_NUM][MAX_VERtEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERtEX_NUM];        //�洢ͼ�ж�������
	AdjMatrix arcs;                         //��ά���飬��¼����֮��Ĺ�ϵ
	int vexnum, arcnum;                      //��¼ͼ�Ķ������ͻ����ߣ���
}MGraph;
//���ݶ��㱾�����ݣ��жϳ������ڶ�ά�����е�λ��
int LocateVex(MGraph * G, VertexType v) {
	int i = 0;
	//����һά���飬�ҵ�����v
	for (; i<G->vexnum; i++) {
		if (G->vexs[i] == v) {
			break;
		}
	}
	//����Ҳ����������ʾ��䣬����-1
	if (i>G->vexnum) {
		printf("no such vertex.\n");
		return -1;
	}
	return i;
}
//��������ͼ/��
void CreateDN(MGraph *G) {
	printf("���붥�����ͱ�����������,��������");
	scanf_s("%d,%d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i<G->vexnum; i++) {
		printf("��¼��������(�����ִ���)��");
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
		printf("���ö����ڽ���Ϣ�������±��ʾ):");
		scanf_s("%d,%d", &v1, &v2); getchar();
		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		if (m == -1 || n == -1) {
			printf("no this vertex\n");
			return;
		}
		G->arcs[n][m].adj = 1;
		G->arcs[m][n].adj = 1;//����ͼ�Ķ��׾��������Խ��߶Գ�
		
		
	}
	//�����ʾ�����
	cout << "ͼ�ľ����ʾ��" << endl;
	for (int i = 0; i < G->vexnum; ++i) {
		for (int j = 0; j < G->vexnum; ++j) {
			cout << G->arcs[i][j].adj << "\t";

		}
		cout << "\n";
	}
}
//��������ͼ/��
void CreateDir(MGraph *G) {
	printf("���붥�����ͱ�����������,��������");
	scanf_s("%d,%d", &(G->vexnum), &(G->arcnum));
	for (int i = 0; i<G->vexnum; i++) {
		printf("��¼��������(�����ִ���)��");
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
		printf("���ö����ڽ���Ϣ�������±��ʾ��:");
		scanf_s("%d,%d", &v1, &v2); getchar();
		int n = LocateVex(G, v1);
		int m = LocateVex(G, v2);
		if (m == -1 || n == -1) {
			printf("no this vertex\n");
			return;
		}
		G->arcs[n][m].adj = 1;

		//G->arcs[m][n].adj = 1;//����ͼ�Ķ��׾��������Խ��߶Գ�
	}
	//�����ʾ�����
	cout << "ͼ�ľ����ʾ��" << endl;
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
		//1.��û����ȵĶ���,��������vexs��
		for (i = 0; i<G->vexnum; i++) {
			for (j = 0; j<G->vexnum; j++) {
				if (G->arcs[j][i].adj != 0)//�����
					break;
			}
			if (j == G->vexnum) {
				//���G->vexs[i]�Ƿ��Ѿ�����
				for (m = 0; m<k; m++)
					if (vexs[m] == G->vexs[i])
						break;
				if (m == k) {
					vexs[k++] = G->vexs[i];
					break;
				}
			}
		}
		//2.û�����Ϊ0�Ķ���
		if (i == G->vexnum) {
			printf("���ڻ�·!\n");
			return;
		}
		//3.ɾ���������ĳ���
		for (j = 0; j<G->vexnum; j++)
			G->arcs[i][j].adj = 0;
	}
	//��������Ľ��
	printf("������������\n");
	for (i = 0; i<k; i++)
		printf("%-3d", vexs[i]);
	printf("\n");
}
///////////////////////////////////////////////////////
int FirstAdjVex(MGraph G, int v)
{
	//�����������±�Ϊv�Ķ���֮���бߵĶ��㣬�������������е��±�
	for (int i = 0; i<G.vexnum; i++) {
		if (G.arcs[v][i].adj) {
			return i;
		}
	}
	return -1;
}
int NextAdjVex(MGraph G, int v, int w)
{
	//��ǰһ������λ��w����һ��λ�ÿ�ʼ������֮���бߵĶ���
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
	visited[v] = True;//���ΪTrue
	visitVex(G, v); //���ʵ�v ������
					//�Ӹö���ĵ�һ���߿�ʼ��һֱ�����һ���ߣ��Դ��ڱ���һ�˵Ķ������DFS����
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
		//����ö���ı��λFalse��֤��δ�����ʣ��������������������
		if (!visited[w]) {
			DFS(G, w);
		}
	}
}
//�����������
void DFSTraverse(MGraph G) {//
	printf("������ȱ������У�");
	int v;
	//��������ǵ�visit�����ʼ��ΪFalse
	for (v = 0; v < G.vexnum; ++v) {
		visited[v] = False;
	}
	//����ÿ�����ΪFalse�Ķ���������������������
	for (v = 0; v < G.vexnum; v++) {
		//����ö���ı��λΪFalse����������������������
		if (!visited[v]) {
			DFS(G, v);
		}
	}
}