#include<iostream>
#include<iomanip>
#include<cmath>
#include"Matrix.h"
using namespace std;

/**********************************
* 功能：在内部实现矩阵卷积
* 参数：待卷积矩阵matrix，卷积核conv_kernel,待卷积矩阵的行列数
*		is_normalize:是否需要除以卷积核的和
**********************************/
int* inner_conv(int* matrix, int* conv_kernel, int nrows, int ncols,bool is_normalize)
{
	int kernel_sum = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			kernel_sum += conv_kernel[i * 3 + j];
	int* result = new(nothrow) int[nrows * ncols];
	if (result == NULL)
	{ 
		cout << "内存分配失败！" << endl;
		exit(0);
	}
		
	int val = 0;
	memset(result, 0, sizeof(int)*nrows * ncols);
	for(int i=1;i<=nrows;i++)
		for (int j = 1; j <= ncols; j++)
		{
			val = 0;
			for (int k = -1; k <= 1; k++)
				for (int m = -1; m <= 1; m++)
				{
					val += matrix[(i + k) * (ncols + 2) + j + m] * conv_kernel[(k+1) * 3 + m+1];
					//cout << "这是matrix " << matrix[(i + k) * (ncols + 2) + j + m] << ' ' ;
					//cout << "这是kernel " << conv_kernel[(i + k) * 3 + j + m] << ' ' << endl;
				}
			if(is_normalize==false)
				result[(i - 1)*ncols+j - 1] = val;
			else
			{
				if (kernel_sum != 0)
					val /= kernel_sum;
				if (val > 255)
					val = 255;
				else if (val < 0)
					val = 0;
				result[(i - 1) * ncols + j - 1] = val;
			}
		}
	return result;
}

/**********************************
功能：实现矩阵卷积的功能
**********************************/
void conv()
{
	const char* content = "卷积";
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

		int* matrix = new(nothrow) int[(nrows+2) * (ncols+2)];
		if (matrix == NULL)
		{
			cout << "内存分配失败" << endl;
			return;
		}
		memset(matrix, 0, sizeof(int) * ((nrows + 2) * (ncols + 2)));
		int conv_kernel[9];

		cout << "请输入待卷积的矩阵: " << endl;
		input_matrix(matrix, nrows, ncols,true);
		cout << "trial" << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
				cout << matrix[i * 5 + j]<<' ';
			cout << endl;
		}
		cout << "请输入卷积核: " << endl;
		input_matrix(conv_kernel, 3, 3);
		output_matrix(conv_kernel, 3,3);

		int* result = inner_conv(matrix, conv_kernel, nrows, ncols);
		cout << "卷积后的矩阵为" << endl;
		output_matrix(result, nrows, ncols);
		delete []result;
		delete []matrix;
		matrix = result = NULL;
		int re = return_menu();
		if (re == 0)
			break;
	}
}