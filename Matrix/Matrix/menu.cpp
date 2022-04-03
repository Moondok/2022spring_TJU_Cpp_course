#include<iostream>
#include<iomanip>
#include<conio.h>
#include "Matrix.h"
using namespace std;


/*****************************
*功能：打印程序开始时的主菜单
*****************************/
char present_menu()
{
	const char* orders[9] = {"矩阵加法","矩阵数乘","矩阵转置",
						     "矩阵乘法","Hadamard乘积","矩阵卷积",
							 "卷积应用","OTSU算法","退出系统"};
	const int length = 60;
	const int height = 3;
	for (int i = 0; i < length; i++)
		cout << "*";
	cout << endl;
	for (int i = 1; i <= 9; i++)
	{
		if ((i - 1) % 3 == 0)
			cout << " *";
		cout << "    " << i % 9 << ' ' <<setiosflags(ios::left)<< setw(12) << orders[i - 1];
		cout << resetiosflags(ios::left);//重新回到右对齐
		if (i % 3 == 0)
			cout << "   *" << endl;
	}
	for (int i = 0; i < length; i++)
		cout << "*";
	cout << endl;
	cout << "选择菜单项<0-8>: ";
	char choice;

	choice = _getch();
		
	return choice;
	
}