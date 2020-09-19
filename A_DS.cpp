// A_DS.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "*******************�㷨�����ݽṹ******************\n";
	cout << "* 1  ������Ļ���������Ӧ��                       *\n";
	cout << "* 2  ջ�Ļ���������Ӧ��                           *\n";
	cout << "* 3  ����Ļ���������Ӧ��                         *\n";
	cout << "* 4  ���Ļ���������Ӧ��                           *\n";
	cout << "* 5  ͼ�Ļ���������Ӧ��                           *\n";
	cout << "* 6  �˳�                                         *\n";
	cout << "***************************************************\n";
}

void LinkListModule() {

	int choice;
	cout << "* 1  ������Ĭ�ϣ�                                 *\n";
	//��ʼ������
	printf("�����ʼ������Ϊ(-1ֹͣ)��\n");
	link *p = initLink();
	int add, elem;
	display(p);
	do {
		cout << "\n";
		cout << "**************������Ļ���������Ӧ��***************\n";
		cout << "* 1  ��������ʾ��                                 *\n";
		cout << "* 2  ����                                         *\n";
		cout << "* 3  ɾ��                                         *\n";
		cout << "* 4  ����                                         *\n";
		cout << "* 5  ��ʾ                                         *\n";
		cout << "* 6  ͨѶ¼��Ӧ�ã�                               *\n";
		cout << "* 7  �˳�                                         *\n";
		cout << "***************************************************\n";
		cout << "��ѡ��";
		cin >> choice;
		switch (choice) {
		case 1:
		{
			cout << "--------��������-------\n\n";
			display(p);
			break;
		}
		case 2:
		{

			cout << "--------����Ԫ��-------\n\n";
			printf("�ڵڼ���λ�ò���Ԫ�أ�\n");
			int add, elem;
			scanf_s("%d%d", &add, &elem);
			p = insertElem(p, elem, add);
			display(p);
			break;
		}

		case 3:
		{

			cout << "--------ɾ��Ԫ��-------\n\n";
			printf("ɾ���ڼ���Ԫ��:\n");
			scanf_s("%d", &add);
			p = delElem(p, add);
			display(p);
			break;
		}

		case 4:
		{

			cout << "--------����Ԫ��-------\n\n";
			printf("����Ԫ�أ�\n");
			scanf_s("%d", &add);
			int address = selectElem(p, add);
			if (address == -1) {
				printf("û�и�Ԫ��\n");
			}
			else {
				printf("Ԫ�ص�λ��Ϊ��%d\n", address);
			}
			break;
		}

		case 5:
		{

			cout << "--------��ʾ����-------\n\n";
			display(p);
			break;
		}

		case 6:
		{

			cout << "--------ͨѶ¼---------\n\n";

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
	//��ʼ��ջ
	lineStack * stack = NULL;
	int elem = 0;
	do {
		cout << "\n";
		cout << "****************ջ�Ļ���������Ӧ��*****************\n";
		cout << "* 1  ��ջ                                         *\n";
		cout << "* 2  ��ջ                                         *\n";
		cout << "* 3  ȡջ��Ԫ��                                   *\n";
		cout << "* 4  ���ʽ��⣨Ӧ�ã�                           *\n";
		cout << "* 5  �˳�                                         *\n";
		cout << "***************************************************\n";
		cout << "��ѡ��";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "--------��ջ(Input one)-------\n\n";
			cin >> elem;
			stack = push(stack, elem);
			display(stack);
			break;
		case 2:
			cout << "--------��ջ-------\n\n";
			stack = pop(stack);
			display(stack);

			break;
		case 3:
			cout << "--------ȡջ��Ԫ��-------\n\n";
			getTop(stack);
			display(stack);

			break;
		case 4:
			cout << "--------���ʽ��ֵ-------\n\n";

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
	cout << "* 1  ����(Ĭ�ϴ���)                                    *\n";

	cout << "������һ����" << endl;
	TSMatrix M;
	M = create();
	display(M);

	cout << "�����ڶ�����" << endl;
	TSMatrix T;
	T = create();
	display(T);

	do {
		cout << "\n";
		cout << "*************ϡ������ѹ���洢��Ӧ��**************\n";
		cout << "* 1  ����(��ʾ)                                    *\n";
		cout << "* 2  ��ʾ                                         *\n";
		cout << "* 3  ����˷���Ӧ�ã�                             *\n";
		cout << "* 4  �˳�                                         *\n";
		cout << "***************************************************\n";
		cout << "��ѡ��";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "---------����-------\n\n";
			display(M);
			break;
		case 2:
			cout << "---------��ʾ-------\n\n";
			display(M);
			break;
		case 3:
			cout << "---------����˷�-------\n\n";
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
	cout << "* 1  ������������Ĭ�������죩                                 *\n";
	cout << "����������:# ��ʾ�ս��" << endl;
	BiTree T;
	T = CreateBiTree();
	char ch;
	int height = 0, count = 0;
	int choice;
	do {
		cout << "\n";
		cout << "**************�������Ļ���������Ӧ��***************\n";
		cout << "* 1  ��������������ʾ��                            *\n";
		cout << "* 2  ��������������/��/��                       *\n";
		cout << "* 3  �����������                                 *\n";
		cout << "* 4  ����Ҷ�ӽ�����                             *\n";
		cout << "* 5  ����˫��                                     *\n";
		cout << "* 6  �����ֵ�                                     *\n";
		cout << "* 7  Huffman���루Ӧ�ã�                          *\n";
		cout << "* 8  �˳�\n";
		cout << "***************************************************\n";
		cout << "��ѡ��";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "---------����������--------\n\n"; break;
		case 2:
			cout << "---------*����������-------\n\n";
			printf("�������:\n");
			PreTraversingBiTree(T); printf("\n");
			printf("�������:\n");
			MidTraversingBiTree(T); printf("\n");
			printf("�������:\n");
			PostTraversingBiTree(T); printf("\n");
			break;
		case 3:
			cout << "---------�����������------\n\n";
			height = Maxdepth(T);
			printf("�߶ȣ�%d\n", height);
			break;
		case 4:
			cout << "---------����Ҷ�ӽ�����-------\n\n";
			Countleaf(T, count);
			printf("Ҷ�ӽ�������%d\n", count);//printf��&�ǵ�ַ
			break;
		case 5:
			cout << "---------����˫��-------\n\n";
			cout << "����������" << endl;
			cin >> ch;
			getParents(T, ch);
			break;
		case 6:
			cout << "---------�����ֵ�-------\n\n";
			cout << "����������" << endl;
			cin >> ch;
			getBrothers(T, ch);
			break;
		case 7:
			cout << "---------Huffman����-------\n\n";
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
		cout << "****************ͼ�Ļ���������Ӧ��*****************\n";
		cout << "* 1  ��������ͼ                                    *\n";
		cout << "* 2  ����������                                    *\n";
		cout << "* 3  ��������ͼ                                    *\n";
		cout << "* 4  ����������                                    *\n";
		cout << "* 5  ����                                          *\n";
		cout << "* 6  ��������                                      *\n";
		cout << "* 7  ��С��������Ӧ�ã�                            *\n";
		cout << "* 8  ���·����Ӧ�ã�                              *\n";
		cout << "* 9  �ؼ�·����Ӧ�ã�                              *\n";
		cout << "* 10 �˳�                                          *\n";
		cout << "***************************************************\n";
		cout << "��ѡ��";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "---------��������ͼ-------\n\n";
			MGraph GN;//����һ��ͼ�ı���
			CreateDN(&GN);//��ʼ��ͼ
			ttt = 1;
			break;
		case 2:
			cout << "---------����������-------\n\n";
			MGraph G;//����һ��ͼ�ı���
			CreateDN(&G);//��ʼ��ͼ
			ttt = 2;
			break;
		case 3:
			cout << "---------��������ͼ-------\n\n";
			MGraph DG;//��������ͼ
			CreateDir(&DG);
			ttt = 3;
			break;
		case 4:
			cout << "---------����������-------\n\n";
			MGraph DGN;//����������
			CreateDir(&DGN);
			ttt = 4;
			break;
		case 5:
			cout << "---------����-------\n\n";
			if (ttt == 1)	DFSTraverse(GN); cout << "\n";//�����������ͼ
			if (ttt == 2)	DFSTraverse(G); cout << "\n";//�����������ͼ
			if (ttt == 3)	DFSTraverse(DG); cout << "\n";//�����������ͼ
			if (ttt == 4)	DFSTraverse(DGN); cout << "\n";//�����������ͼ

			break;
		case 6:
			cout << "---------��������-------\n\n";
			if (ttt == 3)	TopologicalSort(&DG);

			if (ttt == 4)	TopologicalSort(&DGN);

			break;
		case 7:
			cout << "---------��С������-------\n\n"; break;
		case 8:
			cout << "---------���·��-------\n\n"; break;
		case 9:
			cout << "---------�ؼ�·��-------\n\n"; break;
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
		cout << "��ѡ��";
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




