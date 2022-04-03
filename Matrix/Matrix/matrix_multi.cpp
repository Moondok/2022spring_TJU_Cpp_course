#include<iostream>
#include<iomanip>
#include<cmath>
#include"Matrix.h"
using namespace std;

/**************************************
功能：在内部实现矩阵乘积
参数：左矩阵，右矩阵，左矩阵行数，左矩阵列数（右矩阵行数），右矩阵列数
返回值：指向运算结果的指针
*************************************/
int* inner_matrimulti(int* left_matrix, int* right_matrix, int nrows, int npivot, int ncols)
{
	int* result = new(nothrow) int[nrows * ncols];
	if (result == NULL)
	{
		cout << "内存分配失败" << endl;
		exit(0);
	}
	memset(result, 0, sizeof(int) * (nrows * ncols));
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			for (int k = 0; k < npivot; k++)
				result[i * ncols + j] += left_matrix[i * npivot + k] * right_matrix[k * ncols + j];
	return result;
}

/***************************
功能：实现矩阵乘法的功能
*************************/
void matrimulti()
{
	const char* content = "乘法";
	while (true)
	{
		present_title(content);
		int nrows, npivot, ncols;

		cout << "\n输入左矩阵的大小：";
		nrows = input_size(0);
		if (nrows == 0)
			break;
		npivot = input_size(1);
		if (npivot == 0)
			break;

		cout << "\n输入右矩阵的大小(仅列数): ";
		ncols = input_size(1);
		if (ncols == 0)
			break;


		int* left_matrix = new(nothrow) int[nrows * npivot];
		if (left_matrix == NULL)
		{
			cout << "内存分配失败" << endl;
			return;
		}
		int* right_matrix = new (nothrow) int[npivot * ncols];
		if (right_matrix == NULL)
		{
			cout << "内存分配失败" << endl;
			return;
		}
		

		cout << "\n请输入左矩阵: ";
		input_matrix(left_matrix, nrows, npivot);

		cout << "\n请输入右矩阵: ";
		input_matrix(right_matrix, npivot, ncols);

		int* result = inner_matrimulti(left_matrix, right_matrix, nrows, npivot, ncols);
		cout << endl;
		output_matrix_multi(left_matrix, right_matrix,  result, nrows, npivot, ncols);

		delete[] left_matrix;
		delete[] right_matrix;
		delete[] result;
		left_matrix = right_matrix = result = NULL;
		int re = return_menu();
		if (re == 0)
			break;
	}
}

/************************
功能：输出矩阵乘法的算式
参数：左矩阵matrix1,右矩阵matrix2 ,结果矩阵result
	  左矩阵行数，左矩阵列数（右矩阵行数），右矩阵列数
**************************/
void output_matrix_multi(int* matrix1, int* matrix2, int* result, int nrows, int npivot, int ncols)
{
	cout << "该矩阵乘积运算如下" << endl;
	
	cout << "┏" << setw(4 * npivot + 2) << "┓";
	cout << "     ";
	for (int i = 0; i < 2; i++)
	{
		cout << "┏" << setw(4 * ncols + 2) << "┓";
		cout << "     ";
	}
	cout << endl;

	int i;
	int mid = min(nrows, npivot) / 2;
	for (i = 0; i < min(nrows,npivot); i++)
	{
		cout << "┃";
		for (int j = 0; j < npivot; j++)
			cout << setw(4) << matrix1[npivot * i + j];
		cout << "┃";

		if (i == mid)
			cout << setw(3) << "x" << "  ";
		else
			cout << "     ";

		cout << "┃";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << matrix2[ncols * i + j];
		cout << "┃";

		if (i == mid)
			cout << setw(3) << "=" << "  ";
		else
			cout << setw(5) << ' ';

		cout << "┃";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << result[ncols * i + j];
		cout << "┃" << endl;
	}
	if (npivot > nrows)
	{
		cout << "┗" << setw(4 * npivot + 2) << "┛";
		cout << "     ";
		cout << "┃";
		for (int j = 0; j < ncols; j++)
		{
			cout << setw(4) << matrix2[ncols * i + j];
		}
		cout << "┃";
		cout << "     ";
		cout << "┗" << setw(4 * ncols + 2) << "┛";
		cout << "     " << endl;
		i++;
		for (i; i < npivot; i++)
		{
			cout << setw(4*npivot+2+5) << ' ';
			cout << "┃";
			for (int j = 0; j < ncols; j++)
				cout << setw(4) << matrix2[ncols * i + j];
			cout << "┃" << endl;
		}
		cout << setw(4*npivot +2+5) << ' ';
		cout << "┗" << setw(4 * ncols + 2) << "┛";
	}
	else if(npivot<nrows)
	{
		cout << "┃";
		for (int j = 0; j < npivot; j++)
			cout << setw(4) << matrix1[npivot * i + j] ;
		cout << "┃";
		cout << "     ";
		cout << "┗" << setw(4 * ncols + 2) << "┛" << "     ";
		cout << "┃";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << result[ncols * i + j];
		cout << "┃"<< endl;
		i++;

		for (i; i < nrows; i++)
		{
			cout << "┃";
			for (int j = 0; j < npivot; j++)
				cout << setw(4) << matrix1[npivot * i + j];
			cout << "┃"; 
			cout << setw(4*ncols + 12) << ' ';
			cout << "┃";
			for (int j = 0; j < ncols; j++)
				cout << setw(4) << result[ncols * i + j];
			cout << "┃"<< endl;
		}
		
		cout << "┗" << setw(4 * npivot + 2) << "┛";
		cout << setw(4 * ncols + 12) << ' ';
		cout << "┗" << setw(4 * ncols + 2) << "┛";
	}
	else
	{
		cout << "┗" << setw(4 * npivot + 2) << "┛";
		cout << "     ";
		cout << "┗"<< setw(4 * ncols + 2) << "┛";
		cout << "     ";
		cout << "┗" << setw(4 * ncols + 2) << "┛";
		cout << "     " << endl;

	}
	cout << endl;
}