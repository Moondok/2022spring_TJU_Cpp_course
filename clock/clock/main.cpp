#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<graphics.h>
#include <conio.h>
#include<stdlib.h>
#include<time.h>
#include<cmath>  
#include"clock.h"
using namespace std;

/*********************************************
* 功能：实时绘制出雪花和指针
* 参数:当前所有雪花的位置信息
* *******************************************/
void pointer(Point *SNOW)
{
    tm t;
    time_t now;
    time(&now);
    localtime_s(&t, &now);	// 获取当地时间
    int second = t.tm_sec;
    int minute = t.tm_min;
    int hour = t.tm_hour-12;  //24时变为12时
    Point origin = { 0,0 };   //圆心
    Point pointer_points[9];

    //秒针
    pointer_points[0].x = int(190 * sin(PI / 30.0*second));
    pointer_points[0].y = int(-190 * cos(PI / 30.0*second));
    pointer_points[1].x = int(35 * sin(PI / 30.0 * second + PI / 18.0));
    pointer_points[1].y = int(-35 * cos(PI / 30.0 * second + PI / 18.0));
    pointer_points[2].x = int(35 * sin(PI / 30.0 * second - PI / 18.0));
    pointer_points[2].y = int(-35 * cos(PI / 30.0 * second - PI / 18.0));

    //分针
    pointer_points[3].x = int(140 * sin(PI / 30.0 * (minute+second/60.0)));
    pointer_points[3].y = int(-140 * cos(PI / 30.0 * (minute + second / 60.0)));
    pointer_points[4].x = int(30 * sin(PI / 30.0 * (minute + second / 60.0)+PI/15.0));
    pointer_points[4].y = int(-30 * cos(PI / 30.0 * (minute + second / 60.0)+PI/15.0));
    pointer_points[5].x = int(30 * sin(PI / 30.0 * (minute + second / 60.0)-PI/15.0));
    pointer_points[5].y = int(-30 * cos(PI / 30.0 * (minute + second / 60.0)-PI/15.0));

    //时针
    pointer_points[6].x = int(100 * sin(PI / 6.0 * (hour+(60.0*minute+second)/3600.0))); 
    pointer_points[6].y = int(-100 * cos(PI / 6.0 * (hour+(60.0 * minute + second) / 3600.0)));
    pointer_points[7].x = int(35 * sin(PI / 6.0 * (hour + (60.0 * minute + second) / 3600.0)+PI/12.0));
    pointer_points[7].y = int(-35 * cos(PI / 6.0 * (hour + (60.0 * minute + second) / 3600.0)+PI/12.0));
    pointer_points[8].x = int(35 * sin(PI / 6.0 * (hour + (60.0 * minute + second) / 3600.0)-PI/12.0)); 
    pointer_points[8].y = int(-35 * cos(PI / 6.0 * (hour + (60.0 * minute + second) / 3600.0)-PI/12.0));
    setlinecolor(BLACK);

    setlinestyle(BS_SOLID, 1);
    double params[3] = { 0.75,3,0 };
    for (int i = 0; i < 3; i++) //分别是时针，分针，秒针
    {
        line(pointer_points[3*i].x, pointer_points[3*i].y, pointer_points[3*i+1].x, pointer_points[3*i+1].y);
        line(pointer_points[3*i].x, pointer_points[3*i].y, pointer_points[3*i+2].x, pointer_points[3*i+2].y);
        line(pointer_points[3 * i + 1].x, pointer_points[3 * i + 1].y, 0, 0);
        line(pointer_points[3 * i + 2].x, pointer_points[3 * i + 2].y, 0, 0);
        lineSDF(pointer_points[3*i], pointer_points[3*i+1], 1, BLACK, params, 5 );
        lineSDF(pointer_points[3*i], pointer_points[3*i+2], 1, BLACK, params, 5 );
        lineSDF(origin, pointer_points[3 * i + 1], 1, BLACK, params, 5 );
        lineSDF(origin, pointer_points[3 * i + 2], 1, BLACK, params, 5 );
    }
    setlinestyle(BS_SOLID, 3);
    for (int r = 0; r < BALL_RADIUS; r++)
    {
        setlinecolor(mixcolor(BALL_INNER_COLOR, BALL_OUTER_COLOR, (double(BALL_RADIUS) - r) / double(BALL_RADIUS)));
        circle(0,0,r);
    }
   for (int i = 0; i < SNOW_N; i++)
        draw_koch_curve(SNOW[i]);
}

/*********************************************************
* 功能：对当前画布进行一定的初始化
* 参数：用户输入的选项：0表示显示SSAA和高斯模糊的过程
*                       1表示直接加载背景（已经预先保存好）
* *******************************************************/
void init(int n)
{
    initgraph(width, width);	// 图形方式初始化
    if (n == 0)
    {
        SSAA(2);
        setorigin(width/2, width/2);
        for (int i = 0; i < 5; i++)
            Guassian_blur(NULL, 1);
        
        SetWorkingImage(NULL);
    }
    else
    {
        SetWorkingImage(NULL);
        loadimage(NULL, _T("test.png"));
    }
    setorigin(width/2, width/2);
    setbkmode(TRANSPARENT);
    setlinestyle(PS_SOLID, 5);
    //以下两段循环是最外圈的颜色填充
    for (int i = 181; i < 240; i++)
    {
        setlinecolor(mixcolor(COLOR_OUTER_ROUND1, COLOR_OUTER_ROUND2, (240.0 - i) / 600.0));
        circle(0, 0, i);
    }
    for (int i = 240; i < 275; i++)
    {
        setlinecolor(mixcolor(COLOR_OUTER_ROUND2, COLOR_OUTER_ROUND3, (275.0 - i) / 35.0));
        circle(0, 0, i);
    }
    setticks();      //画刻度
    output_font();    //画数字
    setlinestyle(PS_NULL, 3);
    setfillcolor(COLOR_INNER_ROUND); //最内层

    setlinestyle(PS_SOLID, 3);
    //以下两段循环是中圈的颜色填充
    for (int i = 96; i <= 145; i++)
    {
        setlinecolor(mixcolor(COLOR_MID_ROUND1, COLOR_MID_ROUND2, (145.0 - i) / 49.0)); 
        circle(0, 0, i);
    }
    for (int i = 145; i <= 181; i++)
    {
        setlinecolor(mixcolor(COLOR_MID_ROUND2, COLOR_MID_ROUND3, (181.0 - i) / 36.0)); 
        circle(0, 0, i);
    }
}

int main()
{
    srand((unsigned int)(time(NULL)));
    Point snow_position[SNOW_N];
    for (int i = 0; i < SNOW_N; i++)
    {
        snow_position[i].x = rand() % 630 - 315;
        snow_position[i].y = rand() % 630 - 315;
    }
    
    int n = get_choice();
    
    init(n);
    IMAGE b(width, width);
    setorigin(width/2, width/2);
    getimage(&b, -width/2,-width/2, width,width);
    
    
    SetWorkingImage(NULL);
    
    while (!_kbhit())	// 无键盘操作时进入循环
    {
        BeginBatchDraw();
        putimage(-width/2, -width/2, &b);
        /* 根据新的时间重新绘制时针，分针，秒针，*/
        pointer(snow_position);
        FlushBatchDraw();
        
    }
    char ch=_getch();		// 按任意键准备退出时钟程序
    closegraph();		    // 退出图形界面
	return 0;
}