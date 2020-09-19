#pragma once
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

using namespace std;

/*<-----������---->*/
typedef struct Link {
	int  elem;
	struct Link *next;
}link;

/*<-----������---->*/
link* initLink() {
	link * p = (link*)malloc(sizeof(link));//����һ��ͷ���
	link * temp = p;//����һ��ָ��ָ��ͷ��㣬���ڱ�������
					//��������
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
	link * temp = p;//������ʱ���temp
					//�����ҵ�Ҫ����λ�õ���һ�����
	for (int i = 1; i<add; i++) {
		if (temp == NULL) {
			printf("����λ����Ч\n");
			return p;
		}
		temp = temp->next;
	}
	//����������c
	link * c = (link*)malloc(sizeof(link));
	c->elem = elem;
	//�������в�����
	c->next = temp->next;
	temp->next = c;
	return  p;
}
link* delElem(link * p, int add) {
	link * temp = p;
	//��������ɾ��������һ�����
	for (int i = 1; i<add; i++) {
		temp = temp->next;
	}
	link * del = temp->next;//��������һ��ָ��ָ��ɾ����㣬�Է���ʧ
	temp->next = temp->next->next;//ɾ��ĳ�����ķ������Ǹ���ǰһ������ָ����
	free(del);//�ֶ��ͷŸý�㣬��ֹ�ڴ�й©
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
		printf("����λ����Ч\n"); return p;
	}
	temp->elem = newElem;
	return p;
}
void display(link *p) {
	link* temp = p;//��tempָ������ָ��ͷ���
				   //ֻҪtempָ��ָ��Ľ���next����Null����ִ�������䡣
	cout << "����Ϊ��";
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
/*<-----������---->*/