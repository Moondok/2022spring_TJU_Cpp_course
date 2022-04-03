#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Matrix.h"
using namespace cv;
using namespace std;


/****************************************
*功能：处理矩阵加法和哈达玛乘积
*参数：用户输入的choice用来区分这两种操作
*因为这两种操作都需要输入两个同型矩阵，而且输出格式相同，都是entry-wise的操作
所以将二者在同一个函数中实现
**********************************************/
void matriplus_and_hadamulti(const char choice)
{
    const char* content = NULL;
    content = (choice == '1' ? "加法" : "哈达玛乘积");
    while (true)
    {
        present_title(content);
        int nrows=0, ncols=0;
        nrows = input_size(0);
        if (nrows == 0)
            break;
        ncols = input_size(1);
        if (ncols == 0)
            break;

        int* matrix1 = new(nothrow) int[nrows * ncols];
        if (matrix1 == NULL)
        {
            cout << "内存分配失败" << endl;
            return;
        }
        int* matrix2 = new(nothrow) int[nrows * ncols];
        if (matrix2 == NULL)
        {
            cout << "内存分配失败" << endl;
            return;
        }
        int* result = NULL;

        cout << "\n请输入第一个待进行" << content << "运算的矩阵 : ";
        input_matrix(matrix1, nrows, ncols);
        cout << "\n请输入第二个待进行" << content << "运算的矩阵 : ";
        input_matrix(matrix2, nrows, ncols);

        if (choice == '1')
            result = inner_plus(matrix1, matrix2, nrows, ncols);
        else
            result = inner_hadamulti(matrix1,matrix2, nrows, ncols);

        output_plus_hadam(matrix1, matrix2, result, nrows, ncols,choice);

        delete[] matrix1;
        delete[] matrix2;
        delete[] result;
        matrix1 = matrix2 = result = NULL;
        int re = return_menu();
        if (re == 0)
            break;
    }
}


/****************************************
*功能：实现对矩阵加法，矩阵哈达玛乘积的输出
*参数：两个参与运算的矩阵matrix1,matrix2,运算结果result,两个同型矩阵的行，列以及 
区分二者的参数choice
****************************************/
void output_plus_hadam(int* matrix1, int* matrix2, int* result, int nrows, int ncols, const char choice)
{
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "┏" << setw(4 * ncols + 2) << "┓";
        cout << "     ";
    }
    cout << endl;
    for (int i = 0; i < nrows; i++)
    {
        cout << "┃";
        for (int j = 0; j < ncols; j++)
            cout << setw(4) << matrix1[ncols * i + j];
        cout << "┃" ;

        if (i == nrows / 2)
            if (choice == '1')
                cout << setw(3) << "+" << "  ";
            else
                cout << setw(3) << "○" << "  ";
        else
            cout << "     ";

        cout << "┃";
        for (int j = 0; j < ncols; j++)
            cout << setw(4) << matrix2[ncols * i + j];
        cout << "┃" ;

        if (i == nrows / 2)
            cout << setw(3) << "=" << "  ";
        else
            cout << setw(5) << ' ';

        cout << "┃";
        for (int j = 0; j < ncols; j++)
            cout << setw(4) << result[ncols * i + j];
        cout << "┃" << endl;;
    }
    for (int i = 0; i < 3; i++)
    {
        cout << "┗" << setw(4 * ncols + 2) << "┛";
        cout << "     ";
    }
    cout << endl;
}

int main()
{
    while (true) // 注意该循环退出的条件
    {
        system("cls"); // 清屏函数
        char choice=present_menu(); // 调用菜单显示函数，自行补充完成
        // 按要求输入菜单选择项choice
        if (choice == '0') // 选择退出
        {
            char ch;
            cout << "\n确定退出吗?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
            // 下述矩阵操作函数自行设计并完成（包括函数参数及返回类型等），若选择加分项，请自行补充
            case '1':
                matriplus_and_hadamulti(choice);
                break;
            case '2':
                nummulti();
                break;
            case '3':
                matritrans();
                break;
            case '4':
                matrimulti();
                break;
            case '5':
                matriplus_and_hadamulti(choice);
                break;
            case '6':
                conv();
                break;
            case '7':
                conv_application();
                break;
            case '8':
                OSTU_demo();
                cout << "进入菜单8" << endl;
                break;
            default:
                cout << "\n输入错误，请重新输入" << endl;
                wait_for_enter();
        }
    }
    return 0;
}