#include<iostream>
#include<graphics.h>
#include"clock.h"


void draw_koch_curve(Point& position)
{
	double R = SNOW_SIZE;
	int w = 60;    
	int cnums = 3;    //当前图形有多少条边
	if (position.y > 310)
		position.y = rand() % 10 - 310;  //对雪花坐标y做这个处理是为了使其不断下落
	
	Node *line_set=new Node[300];  //按绘画顺序存放每条边，下面3行先绘出正三角形
	if (line_set == NULL)  // 没分配成功就返回
		return;
	line_set[0].x1 = double(position.x); line_set[0].y1 = double((++position.y)); 
	line_set[0].x2 = double(position.x)-R/2; line_set[0].y2 = double((position.y)) + R / 2 * sqrt(3.0);
	line_set[1].x1 = double(position.x) - R/2; line_set[1].y1 = double((position.y)) + R / 2 * sqrt(3.0);
	line_set[1].x2 = double(position.x)+R/2; line_set[1].y2 = double((position.y)) + R / 2 * sqrt(3.0);
	line_set[2].x1 = double(position.x) + R/2; line_set[2].y1 = double((position.y)) + R / 2 * sqrt(3.0); 
	line_set[2].x2 = double(position.x); line_set[2].y2 = double((position.y));
	
	for (int t = 0; t <3; t++)//做3次分形  
	{
		R = R / 3.0;//新分形出来的正三角形边长

		//每一次分型，一条边开裂成3条，j是数组中待填充格子的下标
		int j = cnums;
		for (int i = 0; i < cnums; i++)  //下面这段循环语句借鉴了codebus
		{
			// 读取线段方向
			double k = atan((line_set[i].y2 - line_set[i].y1) / (line_set[i].x2 - line_set[i].x1)) * 180 /PI;
			if ((line_set[i].x2 - line_set[i].x1) < 0)k += 180;

			// 第一条，剪短
			line_set[i].x2 = line_set[i].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[i].y2 = line_set[i].y1 + sin(double(k) / 180.0 * PI) * R;

			k += w;
			line_set[j].x1 = line_set[i].x2;
			line_set[j].y1 = line_set[i].y2;
			line_set[j].x2 = line_set[j].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[j].y2 = line_set[j].y1 + sin(double(k) / 180.0 * PI) * R;

			k -= 2.0 * w;
			line_set[j + 1].x1 = line_set[j].x2;
			line_set[j + 1].y1 = line_set[j].y2;
			line_set[j + 1].x2 = line_set[j + 1].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[j + 1].y2 = line_set[j + 1].y1 + sin(double(k) / 180.0 * PI) * R;

			k += w;
			line_set[j + 2].x1 = line_set[j + 1].x2;
			line_set[j + 2].y1 = line_set[j + 1].y2;
			line_set[j + 2].x2 = line_set[j + 2].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[j + 2].y2 = line_set[j + 2].y1 + sin(double(k) / 180.0 * PI) * R;

			j += 3;
		}
		cnums = j;
	}
	setfillcolor(WHITE);
	setlinestyle(BS_SOLID, 1);
	setlinecolor(WHITE);
	for (int i = 0; i < cnums; i++)
		line(int(line_set[i].x1),int(line_set[i].y1), 
			int(line_set[i].x2), int(line_set[i].y2));
	
	floodfill(position.x,(position.y) +10,WHITE);  //填充雪花
	delete[]line_set;
	line_set = NULL;
}