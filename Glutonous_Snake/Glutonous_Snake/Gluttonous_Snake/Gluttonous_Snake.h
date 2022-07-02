#pragma once
#ifndef __GLUTTONOUS_SNAKE__  //防卫式声明
#define __GLUTTONOUS_SNAKE__


//三个等级的模式
#define ENTRY_MODE 0
#define JUNIOR_MODE 1
#define SENIOR_MODE 2

//屏幕设置
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
//蛇的状态
#define DEAD 0
#define ALIVE 1

#define EXIT -1

//地图上各种标记的设置
#define SNAKE_BODY 1
#define SNAKE_HEAD 3
#define OBSTACLE 2
#define FOOD_BURGER 4
#define FOOD_CHICKEN 5
#define FOOD_FRUIT 6
#define FOOD_NUM 10

//地图的长宽
#define MAP_WIDTH 45
#define MAP_HEIGHT 40

//四个方向
#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3

#define ROUND_ANGLE 20  //圆角矩形的弧度角度
#define BUTTON_CLICK 1  //按钮被点击
#define NO_BUTTON_CLICK 0 //按钮未被点击

#include<fstream>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<iostream>
#include<ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


//4个class
class Snake;
class Food;
class Obstable;
class Game_Controller;

//坐标结构体
struct coordinate
{
	int x;
	int y;
};

//蛇的一段（一个格子）
struct segment
{
	int x=0; int y=0; 
	segment* next=NULL;
	segment* former = NULL;
};


//蛇的类
class Snake
{
private:
	int length = 0; //长度
	segment* body = NULL; //蛇身链表
	int state = DEAD;
	segment* head=NULL;  //蛇头指针
	segment* tail=NULL;  //蛇尾指针
	int current_direction = WEST;  //当前行进方向
	friend Game_Controller;

public:
	void init();  //初始化
	bool is_dead();  //判定是否死亡
	void append_head();  //增加蛇头
	void delete_tail();   //删去蛇尾巴
	void change_direction(const int new_direction); //更改方向
	void adjust_length();  //调整长度
	void destroy();   //摧毁蛇
	~Snake();
};


//墙类
class Obstacle
{
private:
	friend  Game_Controller;

public:

	void init(); //初始化
	void append();  //添加蛇身

};

//食物类
class Food
{
private:
	int num_burger = 0;  //汉堡数量
	int num_chicken = 0;  //炸鸡数量
	int num_fruit = 0;  //食物数量
	friend Game_Controller;
public:
	int get_num_burger() const
	{
		return num_burger;
	}
	int get_num_chicken() const
	{
		return num_chicken;
	}
	int get_num_fruit() const
	{
		return num_fruit;
	}
	void init(const int mode);  //初始化食物

	void append();  //将蛇身体扩展为食物
};

//游戏控制器类
class Game_Controller 
{
private:
	int mode=-1;  //当前是甚么模式
	int hp=-1;   //当前生命值
	UINT best_score=0;  //当前最高得分
	UINT score = 0;   //当前得分
	char *username = NULL;  //当前用户名

public:
	Game_Controller();
	void portray_firstpage()const;  //画首页// 内嵌一个读鼠标的功能，返回选择的是新游戏/历史游戏
	void portray_rulespage()const;  //显示规则页直到用户主动退出
	void portray_exitpage()const;    //画退出页面
	void portray_toolspage(const int option=2) const;  //画排行榜/历史记录页面

	int get_option();      
	void enter_game();  //进入一盘游戏
	int get_mode();      //获取游戏模式
	void set_mode(const int m);   //设置游戏模式
	void set_score(const int s);  //设置得分
	void set_hp(const int h);   //设置生命值

	void init_settings();    //初始化地图
	void portray_gamepage(Snake& snake,Obstacle&,Food & food);   //画游戏页面
	void single_round(Snake& snake, Obstacle&, Food& food);  //进入游戏逻辑
	void update_scoreboard(const Food& food);             //实时修改计分板UI
	void update_record(const int option=2) const;        //更新文件

	void set_username();   //设置用户名字
	~Game_Controller();
};

//整型转宽字符串
void  int2str(const int n, wchar_t* s);

//获取鼠标点击事件
bool get_button_click(const int x, const int y, const int width, const int height, const COLORREF former_color, const COLORREF latter_color, ExMessage& m, const wchar_t* message,const bool mode=0,COLORREF textcolor=WHITE);
#endif // !__GLUTTONOUS_SNAKE__

