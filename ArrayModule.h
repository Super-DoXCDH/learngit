#pragma once
#include<stdio.h>;
#include<iostream>;
using namespace std;
const int number = 8;
const int row1 = 10;//4x4
const int col1 = 10;
const int row2 = 10;//4x5
const int col2 = 10;

typedef struct {
	int i, j;
	int data;
}triple;
typedef struct {
	triple data[number];
	int n, m, num;
}TSMatrix;

TSMatrix create() {
	TSMatrix M;
	cout << "依次输入行数，列数，非零个数（eg：3 4 5）：" << endl;
	cin >> M.n >> M.m >> M.num;
	for (int k = 0; k < M.num; k++) {
		cout << "依次输入第" << k + 1 << "数所在行，列，数据（eg：1 3 6）：" << endl;
		cin >> M.data[k].i >> M.data[k].j >> M.data[k].data;
	}
	return M;
}
void display(TSMatrix M) {
	for (int i = 1; i <= M.n; i++) {
		for (int j = 1; j <= M.m; j++) {
			int value = 0;
			for (int k = 0; k < M.num; k++) {
				if (i == M.data[k].i && j == M.data[k].j) {
					printf("%d\t", M.data[k].data);
					value = 1;
					break;
				}
			}
			if (value == 0)
				printf("0\t");
		}
		printf("\n");
	}
	printf("\n");

}

void  Multiplication(TSMatrix M, TSMatrix T) {
	int RES[row1][col2] = { 0 };
	int temM[row1][col1] = { 0 };
	int temT[row2][col2] = { 0 };
	int ii = 0, jj = 0, kk = 0;

	for (kk = 0; kk < M.num; kk++) {
		temM[M.data[kk].i - 1][M.data[kk].j - 1] = M.data[kk].data;
	}


	for (kk = 0; kk < T.num; kk++) {
		temT[T.data[kk].i - 1][T.data[kk].j - 1] = T.data[kk].data;
	}

	for (ii = 0; ii<M.n; ii++) {
		for (jj = 0; jj<T.m; jj++) {
			for (kk = 0; kk<M.m; kk++) {
				RES[ii][jj] = RES[ii][jj] + temM[ii][kk] * temT[kk][jj];
			}
		}
	}

	display(M);
	cout << "相乘\n";
	display(T);
	cout << "等于" << endl;
	for (ii = 0; ii < M.m; ii++)
	{
		for (jj = 0; jj < T.m; jj++)
		{
			cout << RES[ii][jj] << "\t";

		}
		cout << "\n";
	}
}

TSMatrix transposeMatrix(TSMatrix M, TSMatrix T) {
	T.m = M.n;
	T.n = M.m;
	T.num = M.num;

	if (T.num) {
		int q = 0;
		for (int col = 1; col <= M.m; col++) {
			for (int p = 0; p<M.num; p++) {
				if (M.data[p].j == col) {
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].data = M.data[p].data;
					q++;
				}
			}
		}
	}
	return T;
}