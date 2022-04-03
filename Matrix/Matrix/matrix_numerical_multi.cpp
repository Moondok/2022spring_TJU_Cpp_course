#include <conio.h>
#include <iostream>
#include<iomanip>
#include "Matrix.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/************************
实现矩阵数乘的功能
*************************/
void nummulti()
{
	const char* content = "数乘";
	while (true)
	{
		present_title(content);

		int nrows, ncols;
		nrows = input_size(0);
		if (nrows == 0)
			break;
		ncols = input_size(1);
		if (ncols == 0)
			break;

		//开始做加法
		int* matrix1 = new(nothrow) int[nrows * ncols];  //采用一维数组
		if (matrix1 == NULL)
		{
			cout << "内存分配失败！" << endl;
			return;
		}

		cout << "\n请输入待进行数乘运算的矩阵: ";
		input_matrix(matrix1, nrows, ncols);
		int multiplier = input_multiplier();
		
		int *result = inner_nummulti(matrix1, nrows, ncols,multiplier);
		output_matrix(result, nrows, ncols);
		delete[]matrix1;
		delete[]result;
		matrix1 = result = NULL;

		int re = return_menu();
		if (re == 0)
			break;
	}
}

/*********************************
功能：在内部实现矩阵数乘
参数：原矩阵，行列数，乘数
返回值：指向结果矩阵的乘积
*******************************/
int* inner_nummulti(int* matrix1, int nrows, int ncols, int multiplier)
{
	int* result = new(nothrow) int[nrows * ncols];
	if (result == NULL)
	{
		cout << "内存分配失败！" << endl;
		exit(0);
	}
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			result[ncols * i + j] = multiplier * matrix1[ncols * i + j];
	return result;
}

/*************************
功能：输入数乘时的乘数
返回值：乘数
***************************/
int input_multiplier()
{
	int multiplier;
	while (true)
	{
		cout << "\n请输入乘数: ";
		cin >> multiplier;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	return multiplier;
}

/******************************
功能：输出矩阵数乘的算式
参数：原矩阵，乘数，结果矩阵，行数，列数
******************************/
void output_matrix_nummulti(int* matrix, int multiplier, int* result,int nrows,int ncols)
{
	cout << "该矩阵数乘运算如下" << endl;
	cout << "┏" << setw(4 * ncols + 2) << "┓";
	cout << "     ";
	cout << "┏" << setw(4 * ncols + 2) << "┓" << endl;;
	for (int i = 0; i < nrows; i++)
	{
		cout << "┃";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << matrix[ncols * i + j];
		cout << "┃" << endl;
		if (i == nrows / 2)
			cout << " x" << setw(3) << multiplier;
		cout << "┃";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << result[ncols * i + j];
		cout << "┃" << endl;
	}
	cout << "┗" << setw(4 * ncols + 2) << "┛";
	cout << "     ";
	cout << "┗" << setw(4 * ncols + 2) << "┛";
}
