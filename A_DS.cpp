// A_DS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
#include "LinkListModule.h"
#include "StackModule.h"
#include "ArrayModule.h"
#include"BiTreeModule.h"
#include "GraphModule.h"
#include "Huffman.h"
#include<string>;

using namespace std;

void ShowMainMenu() {
	cout << "\n";
	cout << "*******************算法与数据结构******************\n";
	cout << "* 1  单链表的基本操作及应用                       *\n";
	cout << "* 2  栈的基本操作及应用                           *\n";
	cout << "* 3  数组的基本操作及应用                         *\n";
	cout << "* 4  树的基本操作及应用                           *\n";
	cout << "* 5  图的基本操作及应用                           *\n";
	cout << "* 6  退出                                         *\n";
	cout << "***************************************************\n";
}

void LinkListModule() {

	int choice;
	cout << "* 1  创建（默认）                                 *\n";
	//初始化链表
	printf("正序初始化链表为(-1停止)：\n");
	link *p = initLink();
	int add, elem;
	display(p);
	do {
		cout << "\n";
		cout << "**************单链表的基本操作及应用***************\n";
		cout << "* 1  创建（显示）                                 *\n";
		cout << "* 2  插入                                         *\n";
		cout << "* 3  删除                                         *\n";
		cout << "* 4  查找                                         *\n";
		cout << "* 5  显示                                         *\n";
		cout << "* 6  通讯录（应用）                               *\n";
		cout << "* 7  退出                                         *\n";
		cout << "***************************************************\n";
		cout << "请选择：";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			cout << "--------创建链表-------\n\n";
			display(p);
			break;
		}
		case 2:
		{

			cout << "--------插入元素-------\n\n";
			printf("在第几个位置插入元素：\n");
			int add, elem;
			scanf_s("%d%d", &add, &elem);
			p = insertElem(p, elem, add);
			display(p);
			break;
		}

		case 3:
		{

			cout << "--------删除元素-------\n\n";
			printf("删除第几个元素:\n");
			scanf_s("%d", &add);
			p = delElem(p, add);
			display(p);
			break;
		}

		case 4:
		{

			cout << "--------查找元素-------\n\n";
			printf("查找元素：\n");
			scanf_s("%d", &add);
			int address = selectElem(p, add);
			if (address == -1) {
				printf("没有该元素\n");
			}
			else {
				printf("元素的位置为：%d\n", address);
			}
			break;
		}

		case 5:
		{

			cout << "--------显示链表-------\n\n";
			display(p);
			break;
		}

		case 6:
		{

			cout << "--------通讯录---------\n\n";

			break;
		}

		case 7:
		{

			allFree(p);
			break;
		}

		default:
		{

			cout << "ERROR!"; break;
		}

		}
	} while (choice != 7);
}

void StackModule() {
	int choice;
	//初始化栈
	lineStack * stack = NULL;
	int elem = 0;
	do {
		cout << "\n";
		cout << "****************栈的基本操作及应用*****************\n";
		cout << "* 1  进栈                                         *\n";
		cout << "* 2  出栈                                         *\n";
		cout << "* 3  取栈顶元素                                   *\n";
		cout << "* 4  表达式求解（应用）                           *\n";
		cout << "* 5  退出                                         *\n";
		cout << "***************************************************\n";
		cout << "请选择：";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "--------进栈(Input one)-------\n\n";
			cin >> elem;
			stack = push(stack, elem);
			display(stack);
			break;
		case 2:
			cout << "--------出栈-------\n\n";
			stack = pop(stack);
			display(stack);

			break;
		case 3:
			cout << "--------取栈顶元素-------\n\n";
			getTop(stack);
			display(stack);

			break;
		case 4:
			cout << "--------表达式求值-------\n\n";

			break;
		case 5:
			allFree(stack);
			break;
		default:
			cout << "ERROR!"; break;
		}
	} while (choice != 5);
}


void ArrayModule() {
	int choice;
	cout << "* 1  创建(默认创建)                                    *\n";

	cout << "创建第一个：" << endl;
	TSMatrix M;
	M = create();
	display(M);

	cout << "创建第二个：" << endl;
	TSMatrix T;
	T = create();
	display(T);

	do {
		cout << "\n";
		cout << "*************稀疏矩阵的压缩存储及应用**************\n";
		cout << "* 1  创建(显示)                                    *\n";
		cout << "* 2  显示                                         *\n";
		cout << "* 3  矩阵乘法（应用）                             *\n";
		cout << "* 4  退出                                         *\n";
		cout << "***************************************************\n";
		cout << "请选择：";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "---------创建-------\n\n";
			display(M);
			break;
		case 2:
			cout << "---------显示-------\n\n";
			display(M);
			break;
		case 3:
			cout << "---------矩阵乘法-------\n\n";
			Multiplication(M, T);
			break;
		case 4:

			break;
		default:
			cout << "ERROR!"; break;
		}
	} while (choice != 4);
}

void BiTreeModule() {
	cout << "* 1  创建二叉树（默认先序构造）                                 *\n";
	cout << "请输入数据:# 表示空结点" << endl;
	BiTree T;
	T = CreateBiTree();
	char ch;
	int height = 0, count = 0;
	int choice;
	do {
		cout << "\n";
		cout << "**************二叉树的基本操作及应用***************\n";
		cout << "* 1  创建二叉树（显示）                            *\n";
		cout << "* 2  遍历二叉树（先/中/后）                       *\n";
		cout << "* 3  计算树的深度                                 *\n";
		cout << "* 4  计算叶子结点个数                             *\n";
		cout << "* 5  查找双亲                                     *\n";
		cout << "* 6  查找兄弟                                     *\n";
		cout << "* 7  Huffman编码（应用）                          *\n";
		cout << "* 8  退出\n";
		cout << "***************************************************\n";
		cout << "请选择：";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "---------创建二叉树--------\n\n"; break;
		case 2:
			cout << "---------*遍历二叉树-------\n\n";
			printf("先序遍历:\n");
			PreTraversingBiTree(T); printf("\n");
			printf("中序遍历:\n");
			MidTraversingBiTree(T); printf("\n");
			printf("后序遍历:\n");
			PostTraversingBiTree(T); printf("\n");
			break;
		case 3:
			cout << "---------计算树的深度------\n\n";
			height = Maxdepth(T);
			printf("高度：%d\n", height);
			break;
		case 4:
			cout << "---------计算叶子结点个数-------\n\n";
			Countleaf(T, count);
			printf("叶子结点个数：%d\n", count);//printf带&是地址
			break;
		case 5:
			cout << "---------查找双亲-------\n\n";
			cout << "输入结点名字" << endl;
			cin >> ch;
			getParents(T, ch);
			break;
		case 6:
			cout << "---------查找兄弟-------\n\n";
			cout << "输入结点名字" << endl;
			cin >> ch;
			getBrothers(T, ch);
			break;
		case 7:
			cout << "---------Huffman编码-------\n\n";
			HuffmanCode();
			break;
		case 8:
			allFree(T);
			break;
		default:
			cout << "ERROR!"; break;
		}
	} while (choice != 8);
}

void GraphModule() {
	int choice;
	int ttt;
	do {
		cout << "\n";
		cout << "****************图的基本操作及应用*****************\n";
		cout << "* 1  创建无向图                                    *\n";
		cout << "* 2  创建无向网                                    *\n";
		cout << "* 3  创建有向图                                    *\n";
		cout << "* 4  创建有向网                                    *\n";
		cout << "* 5  遍历                                          *\n";
		cout << "* 6  拓扑排序                                      *\n";
		cout << "* 7  最小生成树（应用）                            *\n";
		cout << "* 8  最短路径（应用）                              *\n";
		cout << "* 9  关键路径（应用）                              *\n";
		cout << "* 10 退出                                          *\n";
		cout << "***************************************************\n";
		cout << "请选择：";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "---------创建无向图-------\n\n";
			MGraph GN;//建立一个图的变量
			CreateDN(&GN);//初始化图
			ttt = 1;
			break;
		case 2:
			cout << "---------创建无向网-------\n\n";
			MGraph G;//建立一个图的变量
			CreateDN(&G);//初始化图
			ttt = 2;
			break;
		case 3:
			cout << "---------创建有向图-------\n\n";
			MGraph DG;//创建有向图
			CreateDir(&DG);
			ttt = 3;
			break;
		case 4:
			cout << "---------创建有向网-------\n\n";
			MGraph DGN;//创建有向网
			CreateDir(&DGN);
			ttt = 4;
			break;
		case 5:
			cout << "---------遍历-------\n\n";
			if (ttt == 1)	DFSTraverse(GN); cout << "\n";//深度优先搜索图
			if (ttt == 2)	DFSTraverse(G); cout << "\n";//深度优先搜索图
			if (ttt == 3)	DFSTraverse(DG); cout << "\n";//深度优先搜索图
			if (ttt == 4)	DFSTraverse(DGN); cout << "\n";//深度优先搜索图

			break;
		case 6:
			cout << "---------拓扑排序-------\n\n";
			if (ttt == 3)	TopologicalSort(&DG);

			if (ttt == 4)	TopologicalSort(&DGN);

			break;
		case 7:
			cout << "---------最小生成树-------\n\n"; break;
		case 8:
			cout << "---------最短路径-------\n\n"; break;
		case 9:
			cout << "---------关键路径-------\n\n"; break;
		case 10:break;
		default:
			cout << "ERROR!"; break;
		}
	} while (choice != 10);
}

void main() {
	system("color 3F");
	int choice;
	do {
		ShowMainMenu();
		cout << "请选择：";
		cin >> choice;
		switch (choice) {
		case 1:LinkListModule(); break;
		case 2:StackModule(); break;
		case 3:ArrayModule(); break;
		case 4:BiTreeModule(); break;
		case 5:GraphModule(); break;
		case 6:break;
		default:cout << "ERROR!"; break;
		}
	} while (choice != 6);
}




