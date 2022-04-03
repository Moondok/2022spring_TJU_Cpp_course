#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<graphics.h>
#include"clock.h"

/**************************
* 画出表盘上时间数字的函数
/**************************/
void output_font()
{
    LOGFONT fontpro;
    fontpro.lfHeight = 70;                         //高
    fontpro.lfWidth = 25;                          //宽
    fontpro.lfQuality = ANTIALIASED_QUALITY;       //抗锯齿
    fontpro.lfWeight = 3;                          //粗细
    fontpro.lfStrikeOut = false;                   //删除线不要
    fontpro.lfUnderline = false;                   //下划线不要
    fontpro.lfItalic = false;                      //斜体不要
    fontpro.lfOrientation = 0;
    fontpro.lfEscapement = 0;                      //等宽字体
    fontpro.lfCharSet = ANSI_CHARSET;               //ANSI字符集
    fontpro.lfPitchAndFamily = 0;
    _tcscpy(fontpro.lfFaceName, _T("Century"));     //字体
    settextcolor(BLACK);                             //颜色
    settextstyle(&fontpro);
    RECT r = { -40,-254, 40,-190 };                //一个矩形框，规定一个数字的大小
    WCHAR s[3];                                     //这个字符数组用来存放数字转换为字符串的结国
    Point base;                 //base是我们输出每个数字时的基准位置，上述矩形框以它为中心扩张

    const int fontlength = 222;  //写数字的矩形框到圆心的半径
    for (int i = 1; i <= 12; i++)
    {
        base.x = int(fontlength * sin(PI / 6 * i));
        base.y = int(-fontlength * cos(PI / 6 * i));
        r = { base.x - 40,base.y - 32,base.x + 40,base.y + 32 };
        int_to_wchar(i, s);
        drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

}

/*********************
画出12个时间刻度线的函数
*************************/
void setticks()
{
    double params[3] = { 0.5, 3.0, 0 };
    const int shorter_scale = 1;
    setlinecolor(BLACK);
    for (int i = 1; i <= 60; i++)
    {
        if (i % 5 == 0)
        {
            Point A = { int(tickr * sin(PI / 30 * i)), int(-tickr * cos(PI / 30 * i)) };
            Point B = { int(tickR * sin(PI / 30 * i)), int(-tickR * cos(PI / 30 * i)) };
            setlinestyle(BS_SOLID, 4);
            line(int(tickr * sin(PI / 30 * i)), int(-tickr * cos(PI / 30 * i)),
                int(tickR * sin(PI / 30 * i)), int(-tickR * cos(PI / 30 * i)));
            lineSDF(A, B, 4, BLACK, params, 3);
        }
        else
        {
            Point A = { int((tickr + 1) * sin(PI / 30 * i)), int(-(1 + tickr) * cos(PI / 30 * i)) };
            Point B = { int((tickR - 2) * sin(PI / 30 * i)), int(-(-2 + tickR) * cos(PI / 30 * i)) };
            setlinestyle(BS_SOLID, 1);
            line(int((tickr + 1) * sin(PI / 30 * i)), int(-(tickr + 1) * cos(PI / 30 * i)),
                int((tickR - 2) * sin(PI / 30 * i)), int(-(tickR - 2) * cos(PI / 30 * i)));
            lineSDF(A, B, 1, ticks_SDF_color, params, 3);
        }
    }
}