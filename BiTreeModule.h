#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
static int length = 0;//������������

typedef struct BiTNode //��̬��������ڵ�
{
	char data;
	struct BiTNode *lchild, *rchild;//ָ�����Һ��ӵ�ָ��
}BiTNode, *BiTree;

BiTree CreateBiTree()//�������춯̬���������ո��ʾ����
{
	char ch;
	BiTree T;
	cin >> ch;
	//scanf_s("%c", &ch, 1);
	//getchar();//���scanfҪ�����»س�������
	if (ch == '#')
	{
		T = NULL; //'#'��ʾ����
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = ch; //Ϊ��������ֵ
		T->lchild = CreateBiTree();//Ϊ����������ֵ
		T->rchild = CreateBiTree();//Ϊ�Һ���������ֵ
	}
	return T;
}
//getParents(T);
void getParents(const BiTree T,const char& ch)
{
	if (T)
	{
		if ((T->lchild&&T->lchild->data==ch )|| (T->rchild && T->rchild->data == ch)) {
			cout << ch << "��˫���ǣ�" << T->data << endl;
			return;
		}
		getParents(T->lchild, ch);
		getParents(T->rchild, ch);

	}
	
}

//getBrothers(T);
void getBrothers(const BiTree T, const char& ch)
{
	if (T)
	{
		if ((T->lchild&&T->lchild->data == ch)) {
			cout << ch << "���ֵ��ǣ�" << T->rchild->data << endl;
			return;
		}
		else if ((T->rchild && T->rchild->data == ch)) {
			cout << ch << "���ֵ��ǣ�" << T->lchild->data << endl;
			return;
		}
		
		getBrothers(T->lchild, ch);
		getBrothers(T->rchild, ch);

	}

}


//Huffman(T);

//����������ݹ�ʵ��
void PreTraversingBiTree(BiTree T)
{
	if (T)
	{
		printf("%c", T->data);
		PreTraversingBiTree(T->lchild);
		PreTraversingBiTree(T->rchild);
	}
}

//����������ݹ�ʵ��
void MidTraversingBiTree(BiTree T)
{
	if (T)
	{
		MidTraversingBiTree(T->lchild);
		printf("%c", T->data);
		MidTraversingBiTree(T->rchild);
	}
}

//����������ݹ�ʵ��
void PostTraversingBiTree(BiTree T)
{
	if (T)
	{
		PostTraversingBiTree(T->lchild);
		PostTraversingBiTree(T->rchild);
		printf("%c", T->data);
	}
}

//��������
int Maxdepth(BiTree T)
{
	if (!T)           //����������0 
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)          //��������1 
		return 1;

	int left = Maxdepth(T->lchild);
	int right = Maxdepth(T->rchild);
	return left>right ? left + 1 : right + 1; //���ĸ߶� = MAX(�������ĸ߶ȣ��������ĸ߶�) + 1;
}

//��Ҷ�ӽ����
void Countleaf(BiTree T, int& count)
{
	if (!T) return;
	if (T->lchild == NULL && T->rchild == NULL) ++count;
	Countleaf(T->lchild, count);
	Countleaf(T->rchild, count);
}
//free
void allFree(BiTree T)
{
	if (T)
	{
		allFree(T->lchild);
		allFree(T->rchild);
		free(T);
		T = NULL;
		printf("free!");
	}
}










