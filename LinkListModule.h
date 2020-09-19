#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

using namespace std;

/*<-----链表函数---->*/
typedef struct Link {
	int  elem;
	struct Link *next;
}link;

/*<-----链表函数---->*/
link* initLink() {
	link * p = (link*)malloc(sizeof(link));//创建一个头结点
	link * temp = p;//声明一个指针指向头结点，用于遍历链表
					//生成链表
	int num = 1;
	while (num != -1) {
		scanf_s("%d", &num);
		if (num == -1) break;
		link *a = (link*)malloc(sizeof(link));
		a->elem = num;
		a->next = NULL;
		temp->next = a;
		temp = temp->next;
	}

	return p;
}
link* insertElem(link * p, int elem, int add) {
	link * temp = p;//创建临时结点temp
					//首先找到要插入位置的上一个结点
	for (int i = 1; i<add; i++) {
		if (temp == NULL) {
			printf("插入位置无效\n");
			return p;
		}
		temp = temp->next;
	}
	//创建插入结点c
	link * c = (link*)malloc(sizeof(link));
	c->elem = elem;
	//向链表中插入结点
	c->next = temp->next;
	temp->next = c;
	return  p;
}
link* delElem(link * p, int add) {
	link * temp = p;
	//遍历到被删除结点的上一个结点
	for (int i = 1; i<add; i++) {
		temp = temp->next;
	}
	link * del = temp->next;//单独设置一个指针指向被删除结点，以防丢失
	temp->next = temp->next->next;//删除某个结点的方法就是更改前一个结点的指针域
	free(del);//手动释放该结点，防止内存泄漏
	return p;
}
int selectElem(link * p, int elem) {
	link * t = p;
	int i = 1;
	while (t->next) {
		t = t->next;
		if (t->elem == elem) {
			return i;
		}
		i++;
	}
	return -1;
}
link* amendElem(link * p, int add, int newElem) {
	link * temp = p;
	for (int i = 0; i<add; ++i) {
		temp = temp->next;
	}
	if (!temp) {
		printf("插入位置无效\n"); return p;
	}
	temp->elem = newElem;
	return p;
}
void display(link *p) {
	link* temp = p;//将temp指针重新指向头结点
				   //只要temp指针指向的结点的next不是Null，就执行输出语句。
	cout << "链表为：";
	while (temp->next) {
		temp = temp->next;
		printf("%d ", temp->elem);
	}
	printf("\n");
}
void allFree(link *p) {
	link *freeNode = nullptr;
	while (nullptr != p) {
		freeNode = p;
		p = p->next;
		free(freeNode);
		cout << "free!" << endl;

	}
}
/*<-----链表函数---->*/