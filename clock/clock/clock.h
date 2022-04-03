#pragma once
/****************几何常量定义区域**************/
#define width 640  //画布宽度（长度）
#define SNOW_N 40   //有多少雪花
#define PI 3.1415926535897  //圆周率
#define tickR 265  //表盘上刻度的长直径
#define tickr 255   //表盘上刻度的短直径
#define SNOW_SIZE 30  //雪花大小
#define SECOND_HAND_LENGTH 190  //秒针长度
#define MINUTE_HAND_LENGTH 140   //分针长度
#define HOUR_HAND_LENGTH   100    //时针长度
#define SHADOW_RADIUS      280 //阴影圆形的半径
#define SHADOW_X      30           //阴影圆的圆心横坐标
#define SHADOW_Y      25             //阴影圆的圆心纵坐标
#define BALL_RADIUS   12  //中心小球的半径
/*******************************/


/************颜色宏定义区域*********/
#define COLOR_INNER_ROUND 0x9CB7D2
//中圈和最外圈由于都有渐变，每圈有3个颜色,由内向外定义3个颜色
#define COLOR_OUTER_ROUND1 0x88D7BB
#define COLOR_OUTER_ROUND2 0x89B9E3
#define COLOR_OUTER_ROUND3 0x819CB7
#define COLOR_MID_ROUND1 0x9EFAFB
#define COLOR_MID_ROUND2 0x88D2FC
#define COLOR_MID_ROUND3 0x8CCBFD
#define ticks_SDF_color 0x4D4D4D  //对浅色刻度做SDF时用到的线的颜色
#define BACKGROUND_COLOR 0XCCFF66  //背景青绿色
#define SHADOW_COLOR 0x87868B     //阴影颜色
#define BALL_OUTER_COLOR  0x8BECFF   //中心小球的外边缘颜色
#define BALL_INNER_COLOR  0xFFFFFF //中心小球的中心颜色
/***********************/



/***********结构体定义区域**************/
struct Node //一个node代表科赫雪花中正三角形的一条边
{
    double x1, y1;				
    double x2, y2;				
    double R;							// 长度
};
struct Point   //点结构体，横纵坐标
{
    int x;
    int y;
};
/*******************************/


/***************函数声明区域*********************/
//画出表盘上时间数字的函数
void output_font();

void setticks();//画出12个时间刻度线

void draw_koch_curve(Point& position);//画出科赫雪花

//将两个颜色混合，用于画出渐变色
COLORREF mixcolor(COLORREF color1, COLORREF color2, double ratio);  

//针对直线进行SDF算法抗锯齿
void lineSDF(Point A, Point B, int line_width, COLORREF linecolor, double params[], int scale );

//对于背景圆形通过SSAA抗锯齿
void SSAA(int SSAA_times);

//将SSAA_img中的一个小区域做好模糊并返回，被Guassian_blur函数调用
void conv(Point center, const double kernel[3][3], int size, IMAGE* origin);

//将画面左下角的阴影边缘做高斯模糊
void Guassian_blur(IMAGE* SSAA_img, int SSAA_times);

//将数字转化为wchar型的串
void int_to_wchar(int n, WCHAR* s);

//接受用户的输入
int get_choice();

//实时绘制出指针和雪花
void pointer(Point* SNOW);

//对画布进行一定程度的初始化
void init(int n);
/***************************************************/
