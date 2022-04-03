#include<iostream>
#include<graphics.h>
#include"clock.h"

/********************************************
* 功能：将center为中心的正方形（边长为2*size)与卷积核进行卷积并返回
* 参数:
    kernel：卷积核
    origin:指向原图的指针
/***********************************************/
void conv(Point center, const double kernel[3][3], int size, IMAGE* origin)
{
    IMAGE* buffer = new IMAGE(size, size);  //用于暂存卷积结果的画布
    getimage(buffer, center.x - size, center.y - size, 2 * size, 2 * size);
    SetWorkingImage(origin);

    double colorr = 0, colorg = 0, colorb = 0;
    COLORREF re;

    //以下是一个四重循环，上面两层是对卷积中心（不是center!)的循环
    //下面两层是对3*3区域的循环
    for (int i = center.x + 1 - size; i < center.x + size - 1; i++)
        //由于卷积会缩减大小的缘故，我们设定一下范围
        for (int j = center.y + 1 - size; j < center.y + size - 1; j++)
        {
            SetWorkingImage(origin);
            colorr = 0, colorg = 0, colorb = 0;

            //下面这二重循环负责卷好一个3*3区域，得到一个颜色，我们把它放在buffer里面，最后以整图的方式返回这个模糊好的buffer
            for (int k = -1; k <= +1; k++)
                for (int m = -1; m <= 1; m++)
                {
                    colorr += double(GetRValue(getpixel(i + k, m + j))) * kernel[1 + k][1 + m];
                    colorg += double(GetGValue(getpixel(i + k, m + j))) * kernel[1 + k][1 + m];
                    colorb += double(GetBValue(getpixel(i + k, m + j))) * kernel[1 + k][1 + m];
                }
            re = RGB(int(colorr), int(colorg), int(colorb));
            SetWorkingImage(buffer);            //buffer只是需要卷积的一小块，千万注意坐标关系
            putpixel(i - (center.x - size), j - (center.y - size), re);
        }
    SetWorkingImage(origin);
    putimage(center.x - size, center.y - size, buffer);
    delete buffer;
}

/****************************************
* 功能：对图像右下角阴影做高斯模糊
* 参数 :ssaa_img:SSAA算法中的更大的图像
*       ssaa_times；放大倍数
* **************************************/
void Guassian_blur(IMAGE* SSAA_img, int SSAA_times)
{
    const double conv_kernel[3][3] = { 0.0947416,0.118318,0.0947416,
                                       0.118318,0.147761,0.118318,
                                        0.0947416,0.118318,0.0947416 };   //3*3的卷积核

    SetWorkingImage(SSAA_img);             //将工作画布调整为SSAA_img
    Point workingpoint;
    for (int i = 0; i < 81; i++)
    {
        //我们每次转一个小角度，以阴影圆上的一个点（workingpoint)为中心，划定一个正方形做卷积
        workingpoint = { 30 * SSAA_times + int(280 * SSAA_times * sin(4 * PI / 15 + i * PI / 90))
                    ,25 * SSAA_times + int(-280 * SSAA_times * cos(4 * PI / 15 + i * PI / 90)) };
        //开始卷积
        if (i < 9 || i>72)
            conv(workingpoint, conv_kernel, 7, SSAA_img);
        else
            conv(workingpoint, conv_kernel, 15, SSAA_img);
    }
}