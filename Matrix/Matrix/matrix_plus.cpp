#include <conio.h>
#include <iostream>
#include<iomanip>
#include "Matrix.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/***********************************
功能：实现一个矩阵的输出
参数：matrix:指向一个矩阵的指针
      nrows:行数
	  ncols:列数
**********************************/
void output_matrix(int* matrix, int nrows, int ncols)
{
	cout << "\n┏" << setw(4 * ncols+2) << "┓";
	cout << endl;
	for (int i = 0; i < nrows; i++)
	{
		cout << "┃";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << matrix[ncols * i + j];
		cout << "┃" << endl;
	}		
	cout << "┗" << setw(4 * ncols+2) << "┛";
}


/*************************
功能：在内部实现矩阵加法
参数:matrix1,2:指向两个同型矩阵的直线
     nrows:行数
	 ncols:列数
返回值：指向结果的指针
*****************************/
int* inner_plus(int* matrix1, int* matrix2, int nrows, int ncols)
{
	int* sum = new(nothrow) int[nrows * ncols];
	if (sum == NULL)
	{
		cout << "内存分配失败" << endl;
		exit(0);
	}
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			sum[i * ncols + j] = matrix1[i * ncols + j] + matrix2[i * ncols + j];
	return sum;
}