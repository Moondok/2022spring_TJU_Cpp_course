#include<iostream>
#include<graphics.h>
#include"clock.h"
using namespace std;

/************************************
* 功能：将数字转化为宽字符型的字符串
* **************************************/
void int_to_wchar(int n, WCHAR* s)
{
    if (n < 10)
    {
        s[0] = WCHAR(n + '0');
        s[1] = '\0';
    }
    else
    {
        s[0] = WCHAR(n / 10 + '0');
        s[1] = WCHAR(n % 10 + '0');
        s[2] = '\0';

    }
}

/********************************************
* 将color1和color2以 ratio和1-ratio的权重混合
* ************************************************/
COLORREF mixcolor(COLORREF color1, COLORREF color2, double ratio)
{
    COLORREF  re;
    BYTE Bcolor = int(GetBValue(color1) * ratio + GetBValue(color2) * (1 - ratio));
    BYTE Rcolor = int(GetRValue(color1) * ratio + GetRValue(color2) * (1 - ratio));
    BYTE Gcolor = int(GetGValue(color1) * ratio + GetGValue(color2) * (1 - ratio));
    re = RGB(Rcolor, Gcolor, Bcolor);
    return re;
}

/*****************************************
接受用户的输入选项
******************************************/
int get_choice()
{
    cout << "  SSAA抗锯齿以及模糊化过程需要较长时间(约45s)" << endl;
    cout << "  因此，我将处理好的背景存为了test.png以便更快速地显示" << endl;
    cout << "  按1直接加载保存好的图像以快速开始，按0显示SSAA及模糊化过程" << endl;
    
    int n;
    while (true)
    {
        cout << "请输入: ";
        cin >> n;
        if (cin.good() == 0 || (n != 0 && n != 1))
        {
            cout << "输入错误" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
        }
        else
            break;
    }
    return n;
}