#include <conio.h>
#include <iostream>
#include<iomanip>
#include "Matrix.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/************************************
功能：在内部实现哈达玛乘积
参数：两个同型矩阵及其行列数
************************************/
int* inner_hadamulti(int *matrix1,int*matrix2,int nrows,int ncols)
{
	int* result = new(nothrow) int[nrows * ncols];
	if (result == NULL)
	{
		cout << "内存分配失败" << endl;
		exit(0);
	}
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			result[i * ncols + j] = matrix1[i * ncols + j] * matrix2[i * ncols + j];
	return result;
}


