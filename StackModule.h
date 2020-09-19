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
	cout << "当前栈为:";
	while (temp&&temp->data) {
		cout << temp->data << "\t";
		temp = temp->next;
	}
}
void getTop(lineStack* stack) {
	if (stack) {
		printf("栈顶元素：%d\n", stack->data);
	}
	else {
		printf("栈已空\n");
	}
}
lineStack * pop(lineStack * stack) {
	if (stack) {
		lineStack * p = stack;
		stack = stack->next;
		printf("弹栈元素：%d ", p->data);
		if (stack) {
			printf("栈顶元素：%d\n", stack->data);
		}
		else {
			printf("栈已空\n");
		}
		free(p);
	}
	else {
		printf("栈内没有元素");
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