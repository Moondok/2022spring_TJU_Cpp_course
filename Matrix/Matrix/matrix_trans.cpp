#include<iostream>
#include"Matrix.h"
using namespace std;

/*******************************
功能：在内部实现矩阵的转置
参数：原矩阵及其行列数
返回值：指向结果的指针
*************************************/
int* inner_trans(int* matrix, int nrows, int ncols)
{
	int* result = new(nothrow) int[ncols * nrows];
	if (result == NULL)
	{
		cout << "内存分配失败" << endl;
		exit(0);
	}
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			result[j * nrows + i] = matrix[i * ncols + j];
	return result;
}

/************************
功能：实现矩阵的转置功能
****************************/
void matritrans()
{
	const char* content = "转置";
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

		int* matrix = new(nothrow) int[nrows * ncols];
		if (matrix == NULL)
		{
			cout << "内存空间分配失败！" << endl;
			return;
		}
		int* result = inner_trans(matrix,nrows,ncols);
		

		cout << "\n请输入待转置的矩阵: ";
		input_matrix(matrix, nrows, ncols);
		result=inner_trans(matrix, nrows, ncols);
		cout << "转置后的矩阵为" << endl;
		output_matrix(result, ncols, nrows);

		delete []result;
		delete[] matrix;
		matrix = result = NULL;
		int re = return_menu();
		if (re == 0)
			break;
	}
	
}