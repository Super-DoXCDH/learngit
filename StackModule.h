#pragma once
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct lineStack {
	int data;
	struct lineStack * next;
}lineStack;

lineStack* push(lineStack * stack, int a) {
	lineStack * line = (lineStack*)malloc(sizeof(lineStack));
	line->data = a;
	line->next = stack;
	stack = line;
	return stack;
}
void display(lineStack* stack) {
	lineStack *temp = stack;
	cout << "��ǰջΪ:";
	while (temp&&temp->data) {
		cout << temp->data << "\t";
		temp = temp->next;
	}
}
void getTop(lineStack* stack) {
	if (stack) {
		printf("ջ��Ԫ�أ�%d\n", stack->data);
	}
	else {
		printf("ջ�ѿ�\n");
	}
}
lineStack * pop(lineStack * stack) {
	if (stack) {
		lineStack * p = stack;
		stack = stack->next;
		printf("��ջԪ�أ�%d ", p->data);
		if (stack) {
			printf("ջ��Ԫ�أ�%d\n", stack->data);
		}
		else {
			printf("ջ�ѿ�\n");
		}
		free(p);
	}
	else {
		printf("ջ��û��Ԫ��");
		return stack;
	}
	return stack;
}
void allFree(lineStack *stack) {
	lineStack *freeNode = nullptr;
	while (NULL != stack) {
		freeNode = stack;
		stack = stack->next;
		free(freeNode);
		printf("free");
	}
}