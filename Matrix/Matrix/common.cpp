#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include"Matrix.h"
using namespace cv;
using namespace std;

/*********************************
*功能：等一个回车
**********************************/
void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}

/*******************************
*功能：当演示完毕后，得到用户继续当前操作或返回菜单的指令
**********************************/
int return_menu()   //返回0则退出，返回1则继续运算
{
    char order;
    cout << "\n要继续进行当前运算吗？（按N/n返回主菜单，按Y/y继续) :";
    order=_getch();

    int re;
    while (true)
    {
        if (order == 'Y' || order == 'y')
        {
            re = 1;
            break;
        }
        else if(order=='N'||order=='n')
        {
            re = 0;
            break;
        }
        order = _getch();
    }
    return re;
}

/******************************
*功能：输入一个行数/列数
*参数：flag:用于区分当前输入的是行还是列
*************************************/
int input_size(int flag)  //flag为0代表输入行，为1代表输入列,choice代表不同的选项
{
	int size;
	while (true)
	{
		cout << "\n请输入矩阵的" << ((flag == 0) ? "行数" : "列数") << "(按0退出): ";
		cin >> size;
		if (cin.good() == 0)
		{
			cout << "输入不符合要求，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		else if (size > 100 || size < 0)
		{
			cout << "输入范围不正确，请重新输入" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else if (size == 0)
		{
			char ch;
			cout << "\n确定退出吗?(按y/Y退出)" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}
		else
			break;
	}
	return size;
}

/********************************
*功能：实现一个矩阵的输入
*参数：matrix：指针，指向一段将被开辟的空间
       nrows:行数
	   ncols:列数
	   is_conv:当前输入的是否是待卷积的矩阵，如果是，位置会略有差别
*************************************/
void input_matrix(int* matrix, int nrows, int ncols,bool is_conv)
{
	cout << "\n请按照先行后列的顺序输入" << endl;
	for (int i = 0+is_conv; i < nrows+is_conv; i++)
	{
		cout << "\n请输入第" << i + 1-is_conv << "行:";
		for (int j = 0 + is_conv; j < ncols + is_conv; j++)
		{
			cin >> matrix[i * (ncols+2*is_conv) + j];
			if (cin.good() == 0)
			{
				cout << "\n第" << i + 1 - is_conv << "行,第" << j + 1 - is_conv << "列的矩阵元素输入有误，请自该元素起重新输入" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				j--;  //打回去重新输！
			}
		}
	}
	
}

/*****************************
功能;打印每个模块开始前的标题部分
参数:content:字符串常量，存储每个功能的名称
*********************************/
void present_title(const char *content)
{
	system("cls");
	for (int i = 0; i < 70; i++)
		cout << "*";
	cout << endl;
	cout << setw(47) << "本界面进行矩阵" << content << "运算" << endl;
	for (int i = 0; i < 70; i++)
		cout << "*";
}

