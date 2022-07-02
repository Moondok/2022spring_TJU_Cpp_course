
#include<graphics.h>
#include<wchar.h>
#include"Gluttonous_Snake.h"

//工具函数，将整数n转换为宽字符型存储在s中
void  int2str(const int n, wchar_t* s)
{
	if (!n)
	{
		wcscpy_s(s, 2,L"0");
		return;
	}

	int tmp = n;
	int length = 0;
	while (tmp)
	{
		tmp /= 10;
		length++;
	}
	tmp = n;
	for (int i = 0; i < length; i++)
	{
		int j = tmp % 10;
		tmp /= 10;
		s[length - 1 - i] = j + '0';
	}
	s[length] = '\0';

}

//工具函数，用于获取鼠标对于按钮的点击事件
//根据mode不同分为两种不同情况：
//mode=1,只要没点击就返回
//mode=0,只要鼠标还放在上面就等待
bool get_button_click(const int x, const int y, const int width, const int height, const COLORREF former_color, const COLORREF latter_color,ExMessage& m,const wchar_t* message,const bool mode,COLORREF textcolor)
{
	if (mode)
	{
		if (m.x > x + SCREEN_WIDTH / 2 && m.x<x + width + SCREEN_WIDTH / 2 && m.y>y + SCREEN_HEIGHT / 2 && m.y<y + SCREEN_HEIGHT / 2 + height)
		{
			setfillcolor(latter_color);
			solidroundrect(x, y, x + width, y + height, ROUND_ANGLE, ROUND_ANGLE);
			settextcolor(textcolor);
			RECT rect = { x,y,x + width,y + height };
			drawtext(message, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			//getmessage(&m, EM_MOUSE);
			if (m.message == WM_LBUTTONDOWN)
				return BUTTON_CLICK;
			else
			{
				setfillcolor(former_color);
				solidroundrect(x, y, x + width, y + height, ROUND_ANGLE, ROUND_ANGLE);
				drawtext(message, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
				return NO_BUTTON_CLICK;
			}
		}
		else
			return NO_BUTTON_CLICK;

	}
	
	else
	{
		if (m.x > x + SCREEN_WIDTH / 2 && m.x<x + width + SCREEN_WIDTH / 2 && m.y>y + SCREEN_HEIGHT / 2 && m.y<y + SCREEN_HEIGHT / 2 + height)
		{
			setfillcolor(latter_color);
			solidroundrect(x, y, x + width, y + height, ROUND_ANGLE, ROUND_ANGLE);
			settextcolor(textcolor);
			RECT rect = { x,y,x + width,y + height };
			drawtext(message, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			while (m.x > x + SCREEN_WIDTH / 2 && m.x<x + width + SCREEN_WIDTH / 2 && m.y>y + SCREEN_HEIGHT / 2 && y + SCREEN_HEIGHT / 2 + height)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN)
					return BUTTON_CLICK;
			}
			setfillcolor(former_color);
			solidroundrect(x, y, x + width, y + height, ROUND_ANGLE, ROUND_ANGLE);
			drawtext(message, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			return NO_BUTTON_CLICK;
		}
		else
			return NO_BUTTON_CLICK;
	}
}
