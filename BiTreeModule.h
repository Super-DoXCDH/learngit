#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
static int length = 0;//二叉树结点个数

typedef struct BiTNode //动态二叉链表节点
{
	char data;
	struct BiTNode *lchild, *rchild;//指向左右孩子的指针
}BiTNode, *BiTree;

BiTree CreateBiTree()//按先序构造动态二叉树，空格表示空树
{
	char ch;
	BiTree T;
	cin >> ch;
	//scanf_s("%c", &ch, 1);
	//getchar();//多个scanf要用吞下回车！！！
	if (ch == '#')
	{
		T = NULL; //'#'表示空树
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = ch; //为根数据域赋值
		T->lchild = CreateBiTree();//为左孩子数据域赋值
		T->rchild = CreateBiTree();//为右孩子数据域赋值
	}
	return T;
}
//getParents(T);
void getParents(const BiTree T,const char& ch)
{
	if (T)
	{
		if ((T->lchild&&T->lchild->data==ch )|| (T->rchild && T->rchild->data == ch)) {
			cout << ch << "的双亲是：" << T->data << endl;
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
			cout << ch << "的兄弟是：" << T->rchild->data << endl;
			return;
		}
		else if ((T->rchild && T->rchild->data == ch)) {
			cout << ch << "的兄弟是：" << T->lchild->data << endl;
			return;
		}
		
		getBrothers(T->lchild, ch);
		getBrothers(T->rchild, ch);

	}

}


//Huffman(T);

//先序遍历，递归实现
void PreTraversingBiTree(BiTree T)
{
	if (T)
	{
		printf("%c", T->data);
		PreTraversingBiTree(T->lchild);
		PreTraversingBiTree(T->rchild);
	}
}

//中序遍历，递归实现
void MidTraversingBiTree(BiTree T)
{
	if (T)
	{
		MidTraversingBiTree(T->lchild);
		printf("%c", T->data);
		MidTraversingBiTree(T->rchild);
	}
}

//后序遍历，递归实现
void PostTraversingBiTree(BiTree T)
{
	if (T)
	{
		PostTraversingBiTree(T->lchild);
		PostTraversingBiTree(T->rchild);
		printf("%c", T->data);
	}
}

//求最大层数
int Maxdepth(BiTree T)
{
	if (!T)           //空树，返回0 
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)          //树根返回1 
		return 1;

	int left = Maxdepth(T->lchild);
	int right = Maxdepth(T->rchild);
	return left>right ? left + 1 : right + 1; //树的高度 = MAX(左子树的高度，右子树的高度) + 1;
}

//求叶子结点数
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










