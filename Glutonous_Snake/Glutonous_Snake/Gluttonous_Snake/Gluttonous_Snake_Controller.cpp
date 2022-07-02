#define _CRT_SECURE_NO_WARNINGS
#include"Gluttonous_Snake.h"
#include<graphics.h>
#include<conio.h>
unsigned char** map = NULL;

//构造函数
Game_Controller::Game_Controller()
{
	map = new(std::nothrow) unsigned char* [MAP_WIDTH + 1];  //加1是因为不想处理那种下标变换
	if (map == NULL)
		exit(EXIT_FAILURE);
	for (int i = 0; i <= MAP_WIDTH; i++)
	{
		map[i] = new(std::nothrow) unsigned char[MAP_HEIGHT + 1];
		if (map[i] == NULL)
			exit(EXIT_FAILURE);
	}

	username = new char[10];
	strcpy(username, "moondok");
	std::fstream ranks_file;
	ranks_file.open("ranks.log", std::ios::in | std::ios::out | std::ios::_Nocreate);
	if (ranks_file.is_open() == 0)
	{
		best_score = 0;
		ranks_file.open("ranks.log", std::ios::out);
		for (int i = 0; i < 3; i++)//三种模式的排行榜
		{
			ranks_file << 0 << '\n';
			for (int i = 0; i < 3; i++) //取前三名
				ranks_file << "                                                  " << '\n';
		}
		ranks_file.close();
	}

	std::fstream records_file;
	records_file.open("records.log", std::ios::in | std::ios::out | std::ios::_Nocreate);
	if (records_file.is_open() == 0)
	{
		records_file.open("records.log", std::ios::out);
		for (int i = 0; i < 3; i++)//三种模式的记录
		{
			records_file << 0 << '\n';
			for (int i = 0; i < 3; i++) //取最近三条
				records_file << "                                                  " << '\n';
		}
		records_file.close();
	}

}

//绘制首页
void Game_Controller::portray_firstpage()const
{
	initgraph(SCREEN_WIDTH,SCREEN_HEIGHT);
	setbkmode(OPAQUE);

	loadimage(NULL, _T("image/bg.png"));
	
	setorigin(600,400); //调整原点

	setbkmode(TRANSPARENT);

	LOGFONT font_config;
	font_config.lfHeight = 35;

	font_config.lfWidth = 15;
	font_config.lfWeight = 400;
	font_config.lfItalic = false;
	font_config.lfUnderline = false;
	font_config.lfCharSet = ANSI_CHARSET;
	font_config.lfStrikeOut = false;
	font_config.lfQuality = ANTIALIASED_QUALITY;
	font_config.lfEscapement = 0;
	font_config.lfOrientation = 0;
	font_config.lfPitchAndFamily =2 ;

	settextstyle(&font_config);

	setfillcolor(BROWN); //新游戏
	solidroundrect(-100, -20, 100, 30, 20, 20);
	const wchar_t s1[] = L"新游戏";
	settextcolor(WHITE);
	outtextxy(-50, -15, s1);

	solidroundrect(-100, 60, 100, 110, 20, 20);
	const wchar_t s2[] = L"历史游戏";
	outtextxy(-67, 65, s2);

	solidroundrect(-100, 140, 100, 190, 20, 20);
	const wchar_t s3[] = L"排行榜";
	outtextxy(-50, 145, s3);

	solidroundrect(-100, 220, 100, 270, 20, 20);//退出
	const wchar_t s4[] = L"退出游戏";
	outtextxy(-67, 225, s4);
}

//获取玩家从首页通过鼠标点击获取的信息，包括排行榜，新游戏，历史记录和退出游戏四项
int Game_Controller::get_option()
{
	ExMessage m;
	const wchar_t s1[] = L"新游戏";
	const wchar_t s2[] = L"历史游戏";
	const wchar_t s3[] = L"排行榜";
	const wchar_t s4[] = L"退出游戏";
	int option = -1;
	while (1)
	{
		getmessage(&m, EM_MOUSE);//这里我们只想要鼠标事件
		if (m.x > -100 + 600 && m.x<100 + 600 && m.y>-20 + 400 && m.y < 30 + 400)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, -20, 100, 30, 20, 20);
			settextcolor(WHITE);
			outtextxy(-50, -15, s1);
			while (m.x > -100 + 600 && m.x<100 + 600 && m.y>-20 + 400 && m.y < 30 + 400)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN)
					return (option = 0);
				if (!(m.x > -100 + 600 && m.x<100 + 600 && m.y>-20 + 400 && m.y < 30 + 400))
				{
					setfillcolor(BROWN); 
					solidroundrect(-100, -20, 100, 30, 20, 20);
					outtextxy(-50, -15, s1);
					break;
				}
			}
		}
		else if (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>60 + SCREEN_HEIGHT / 2 && m.y < 110 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, 60, 100, 110, 20, 20);
			outtextxy(-67, 65, s2);
			while (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>60 + SCREEN_HEIGHT / 2 && m.y < 110 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == (WM_LBUTTONDOWN))
					return (option = 1);
				if (!(m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>60 + SCREEN_HEIGHT / 2 && m.y < 110 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(BROWN); //新游戏
					solidroundrect(-100, 60, 100, 110, 20, 20);
					outtextxy(-67, 65, s1);
					break;
				}
					
			}
			setfillcolor(BROWN);
			solidroundrect(-100, 60, 100, 110, 20, 20);
			outtextxy(-67, 65, s2);
		}
		else if (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>140 + SCREEN_HEIGHT / 2 && m.y < 190 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, 140, 100, 190, 20, 20);
			outtextxy(-50, 145, s3);
			while (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>140 + SCREEN_HEIGHT / 2 && m.y < 190 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == (WM_LBUTTONDOWN))
					return (option = 2);
				if (!(m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>140 + SCREEN_HEIGHT / 2 && m.y < 190 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(BROWN); //新游戏
					solidroundrect(-100, 140, 100, 190, 20, 20);
					outtextxy(-50,145, s3);
					break;
				}
			}
			setfillcolor(BROWN);
			solidroundrect(-100, 140, 100, 190, 20, 20);
			outtextxy(-50, 145, s3);
		}
		else if (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>220 + SCREEN_HEIGHT / 2 && m.y < 270 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, 220, 100, 270, 20, 20);
			outtextxy(-67,225, s4);
			while (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>220 + SCREEN_HEIGHT / 2 && m.y < 270 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == (WM_LBUTTONDOWN))
					return (option = 3);
				if (!(m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>220 + SCREEN_HEIGHT / 2 && m.y < 270 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(BROWN); //新游戏
					solidroundrect(-100, 220, 100, 270, 20, 20);
					outtextxy(-67, 225, s4);
					break;
				}
			}
			setfillcolor(BROWN);
			solidroundrect(-100, 220, 100, 270, 20, 20);
			outtextxy(-67, 225, s4);
		}
	}
}

//绘制规则页
void Game_Controller::portray_rulespage() const
{

	setfillcolor(0x238E6B);
	solidrectangle(-600, -400, 600, -250);


	RECT rect = { -100,-370,100,-280 };
	const wchar_t rule_page_title[] = L"规则页";
	//outtextxy(-500, -350, rule_page_title);

	settextstyle(60, 0, _T("楷体"));
	drawtext(rule_page_title, &rect, DT_VCENTER | DT_SINGLELINE|DT_CENTER);


	setfillcolor(0x00EEEE);
	solidrectangle(-600, -251, 600, -34);

	setfillcolor(0x00CDCD);
	solidrectangle(-600, -33, 600, 183);

	setfillcolor(0x00FFFF);
	solidrectangle(-600, 184, 600, 400);

	//第一个模式的规则

	const wchar_t* rules[3] =
	{
		L"控制方向键来控制小蛇的前进方向,使蛇吃掉面板上随机位置上的食物。每次成功吃掉食物后小蛇体长将增加一点，得分增加。食物吃光则再次随机产生。当小蛇撞到边界或者蛇头与蛇身相撞时，蛇将挂掉，游戏结束。",
		L"蛇挂掉后，此时蛇尸身改变显示颜色变成边界，再随机产生新的食物和蛇，游戏继续。直到剩余空间不足以生成新的蛇和食物为止。",
		L"蛇挂掉后，此时蛇尸身改变显示颜色变成食物，再随机产生新的食物和蛇，游戏继续。直到撞墙次数>5，或剩余空间不足以生成新的蛇和食物为止"
	};

	const wchar_t* versions[3] =
	{
		L"入门版",L"进阶版",L"高级版"
	};

	const COLORREF rule_page_colors[3] =
	{
		0x00EEEE,0x00CDCD,0x00FFFF
	};


	const wchar_t enter_game_button[] = L"开始游玩";
	//以下循环用来打印三种模式的规则
	
	for (int i = 0; i < 3; i++)
	{
		settextcolor(BLACK);
		setfillcolor(rule_page_colors[i]);  //画背景
		solidrectangle(-600, -251 + 218 * i, 600, -34 + 217 * i);

		rect = { -550,-225+217*i,-450,-190+217*i };
		settextstyle(27, 0, _T("仿宋"), 0, 0, 1000, false, false, false);
		drawtext(versions[i], &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

		rect = { -450,-220 + 217 * i,200,-20 + 217 * i };
		settextstyle(25, 0, _T("宋体"), 0, 0, 600, false, false, false);
		drawtext(rules[i], &rect, DT_LEFT | DT_WORDBREAK);


		setfillcolor(0x00ADCD);  //0xD7FF是按下去的颜色
		solidroundrect(400, -251 + 218 * i + (217 - 170), 550, -34 + 217 * i - 120,20,20);
		rect = { 400, -251 + 218 * i + (217 - 170) ,550, -34 + 217 * i - 120 };
		settextcolor(WHITE);
		settextstyle(25, 0, _T("楷体"), 0, 0, 600, false, false, false);
		drawtext(_T("开始游玩"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	}
	//画出右下角的返回按钮
	setfillcolor(0x238E6B);
	solidroundrect(490, 345, 590, 390,20,20);
	rect = { 490, 345, 590, 390 };
	settextstyle(25, 0, _T("仿宋"), 0, 0, 600, false, false, false);
	settextcolor(WHITE);
	drawtext(_T("返回"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	
}

//得到游戏模式，包括进阶，入门和高级
int Game_Controller::get_mode()
{
	ExMessage m;
	RECT rect;
	while (true)
	{
		getmessage(&m,EM_MOUSE);
		for (int i = 0; i < 3; i++)
		{
			bool tag = m.x > 400+SCREEN_WIDTH/2 && m.x<550 + SCREEN_WIDTH / 2 && m.y>-251 + 218 * i + (217 - 170)+SCREEN_HEIGHT / 2 && m.y < -34 + 217 * i - 120 + SCREEN_HEIGHT / 2;
			if (tag)
			{
				setfillcolor(0xD7FF);
				solidroundrect(400, -251 + 218 * i + (217 - 170), 550, -34 + 217 * i - 120, 20, 20);
				rect = { 400, -251 + 218 * i + (217 - 170) ,550, -34 + 217 * i - 120 };
				settextcolor(WHITE);
				settextstyle(25, 0, _T("楷体"), 0, 0, 600, false, false, false);
				drawtext(_T("开始游玩"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				while (m.x > 400 + SCREEN_WIDTH / 2 && m.x<550 + SCREEN_WIDTH / 2 && m.y>-251 + 218 * i + (217 - 170) + SCREEN_HEIGHT / 2 && m.y < -34 + 217 * i - 120 + SCREEN_HEIGHT / 2)
				{
					getmessage(&m, EM_MOUSE);
					if (m.message == WM_LBUTTONDOWN)
						return i;
					if (!(m.x > 400 + SCREEN_WIDTH / 2 && m.x<550 + SCREEN_WIDTH / 2 && m.y>-251 + 218 * i + SCREEN_HEIGHT / 2 + (217 - 170) && m.y < -34 + 217 * i - 120 + SCREEN_HEIGHT / 2))
					{
						setfillcolor(0x00ADCD);
						solidroundrect(400, -251 + 218 * i + (217 - 170), 550, -34 + 217 * i - 120, 20, 20);
						drawtext(_T("开始游玩"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
						break;
					}
				}
				break;
				
			}
		}
		if (m.x >490+SCREEN_WIDTH/2 && m.x<590+SCREEN_WIDTH/2 && m.y>345+SCREEN_HEIGHT/2&& m.y <390+SCREEN_HEIGHT/2 )
		{
			setfillcolor(0x32CD9A);
			solidroundrect(490, 345, 590, 390, 20, 20);
			rect = { 490,345,590,390 };
			settextstyle(25, 0, _T("仿宋"), 0, 0, 600, false, false, false);
			settextcolor(WHITE);
			drawtext(_T("返回"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

			while (m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN)
					return EXIT;
				if (!(m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(0x238E6B);
					solidroundrect(490, 345, 590, 390, 20, 20);
					drawtext(_T("返回"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
					break;
				}
			}

		}
	}
}

//根据玩家选择的模式对game_controller类中的成员进行设置
void Game_Controller::set_mode(const int m)
{
	
	std::fstream ranks_file("ranks.log", std::ios::in);
	
	ranks_file.seekg(int(double(159)*double(m)), std::ios::beg);
	int num_records = 0;
	ranks_file >> num_records;
	if (num_records == 0)
		best_score = 0;
	else
	{
		ranks_file.seekg(int(double(159) * double(m) + 3), std::ios::beg);
		ranks_file >> best_score;
	}
	ranks_file.close();
	

	mode = m;
	if (mode == 0)
		hp = 1;
	else if (mode == 2)
		hp = 5;
	else if (mode == 1)
		hp = 5;
}

//设置成绩
void Game_Controller::set_score(const int s)
{
	score = s;
}

//设置生命值
void Game_Controller::set_hp(const int h)
{
	hp = h;
}

//初始化全局地图
void Game_Controller::init_settings()
{
	for (int i = 1; i <= MAP_WIDTH; i++)
		for (int j = 1; j <= MAP_HEIGHT; j++)
			map[i][j] = static_cast<unsigned char>(0);//为0就代表是空空的地面
}

//正式进入一种模式的游戏
void Game_Controller::enter_game()
{
	init_settings();
	Snake snake;
	Obstacle obstacle;
	Food food;
	snake.init();
	obstacle.init();
	food.init(mode);

	portray_gamepage(snake, obstacle, food);

	set_username();//得到用户名
	portray_gamepage(snake, obstacle, food);
	(void)_getch();
	single_round(snake, obstacle, food); //开始游戏逻辑
}

//绘制游戏页面
void Game_Controller::portray_gamepage(Snake& snake, Obstacle&, Food& food)
{
	setfillcolor(0x33cccc); //游戏界面左侧背景色
	solidrectangle(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, -SCREEN_WIDTH / 2 + 295, SCREEN_HEIGHT / 2);//宽为300
	setfillcolor(0x006666);
	solidrectangle(-SCREEN_WIDTH / 2 + 296, -SCREEN_HEIGHT / 2, -SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2);//画地图和左侧提示栏的分界线

	RECT rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 30,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 30 + 70 };

	settextcolor(0x333333);
	settextstyle(28, 0, _T("仿宋"),0,0,1000,false,false,false);
	switch (mode)
	{
		case 0:
			drawtext(L"入门版", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case 1:
			drawtext(L"进阶版", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case 2:
			drawtext(L"高级版", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		default:
			break;
	}

	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 150,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 70 };
	drawtext(L"当前得分:",& rect, DT_VCENTER | DT_LEFT);
	wchar_t score_str[21];
	int2str(score, score_str);
	rect.left += 130; rect.top -= 22;  //原来左右边界+80
	rect.right += 15; rect.bottom -= 22;
	drawtext(score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	//*开始输出历史最高分数
	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 200,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 120 };
	drawtext(L"最高得分:", &rect, DT_VCENTER | DT_LEFT);
	wchar_t best_score_str[21];
	int2str(best_score, best_score_str);
	rect.left += 130; rect.top -= 22;  //原来左右边界+80
	rect.right += 15; rect.bottom -= 22;
	drawtext(best_score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);



	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 240,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 240 + 70 };
	drawtext(L"当前生命", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	IMAGE heart;
	loadimage(&heart, _T("image/heart.png"));
	for (int i = 0; i < hp; i++)
		putimage(-SCREEN_WIDTH / 2 +7+56*i, -SCREEN_HEIGHT / 2 + 240 + 60, &heart);



	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 360,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 360 + 70 };
	drawtext(L"当前食物剩余", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	IMAGE burger_icon;
	loadimage(&burger_icon, _T("image/burger_icon.png"));
	putimage(-SCREEN_WIDTH / 2 + 45, 25, &burger_icon);
	rect = { -SCREEN_WIDTH / 2 + 130,35, -SCREEN_WIDTH / 2 + 260,65 };

	wchar_t buffer[16];
	buffer[0] = 'x';
	buffer[1] = ' ';
	buffer[2] = '\0';

	wchar_t str[10];
	int2str(food.get_num_burger(), str);
	wcscat_s(buffer, 10, str);
	
	
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	IMAGE chicken_icon;
	loadimage(&chicken_icon, _T("image/chicken_icon.png"));
	putimage(-SCREEN_WIDTH / 2 + 45, 100, &chicken_icon);
	buffer[2] = '\0';
	rect.top += 80;
	rect.bottom += 80;
	int2str(food.get_num_chicken(), str);
	wcscat_s(buffer, 10, str);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	IMAGE fruit_icon;
	loadimage(&fruit_icon, _T("image/fruit_icon.png"));
	putimage(-SCREEN_WIDTH / 2 + 45, 175, &fruit_icon);
	rect.top += 80;
	rect.bottom += 80;
	buffer[2] = '\0';
	int2str(food.get_num_fruit(), str);
	wcscat_s(buffer, 10, str);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	//此时左边的计分板基本上画完了
	IMAGE wall_image;
	loadimage(&wall_image, _T("image/wall.png"));

	IMAGE burger_image;
	loadimage(&burger_image, _T("image/burger.png"));

	IMAGE chicken_image;
	loadimage(&chicken_image, _T("image/chicken.png"));

	IMAGE fruit_image;
	loadimage(&fruit_image, _T("image/fruit.png"));
	
	for(int i=1;i<=MAP_WIDTH;i++)
		for (int j = 1; j <= MAP_HEIGHT; j++)
		{
			int x = 20 * (i - 1) + 300 - SCREEN_WIDTH / 2, y = 20 * (j - 1) - SCREEN_HEIGHT / 2;
			if (map[i][j] == OBSTACLE)
				putimage(x,y, &wall_image);

			else if (map[i][j] > 3)
			{
				switch (map[i][j])
				{
					case FOOD_BURGER:
						putimage(x, y, &burger_image);
						break;
					case FOOD_CHICKEN:
						putimage(x, y, &chicken_image);
						break;
					case FOOD_FRUIT:
						putimage(x, y, &fruit_image);
						break;
				}
			}
			else
			{
				if (map[i][j] == 0)
					setfillcolor(0X8FF6FF);
				else if (map[i][j] == SNAKE_BODY)
					setfillcolor(BROWN);
				else if (map[i][j] == SNAKE_HEAD)
					setfillcolor(0X2f6b55);

				fillrectangle(x, y, x+20, y+20);
			}
		}

	//现在要画一个返回按钮
	setfillcolor(BROWN);
	solidroundrect(-SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT /2 -60, -SCREEN_WIDTH / 2 + 300 - 80, SCREEN_HEIGHT/2 - 15,20,20);
	rect = { -SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT/2 - 60, -SCREEN_WIDTH / 2 + 300 - 80, SCREEN_HEIGHT /2- 15 };
	settextcolor(WHITE);
	drawtext(_T("退出"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	
}

//当玩家在游戏途中选择退出键时，暂停游戏并绘制以下的退出页面
void Game_Controller::portray_exitpage()const
{
	setfillcolor(0xDCF8FF);
	solidroundrect(-150,-75,150,75,ROUND_ANGLE,ROUND_ANGLE);
	RECT rect = {-150,-70,150,0};

	settextcolor(BROWN);
	drawtext(_T("确认退出？"),&rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	rect = {-120,20,-30,60};
	setfillcolor(0xCDEBFF);
	solidroundrect(-120,20,-30,60,ROUND_ANGLE,ROUND_ANGLE);
	drawtext(_T("确认"),&rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	rect = {30,20,120,60};
	solidroundrect(30,20,120,60,ROUND_ANGLE,ROUND_ANGLE);
	drawtext(_T("返回"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

}

//正式进入一种模式的游戏逻辑
void Game_Controller::single_round(Snake& snake, Obstacle&obstacle, Food& food)
{
	
	char ch='\0';
	ExMessage m;
	flushmessage();
	while (hp)
	{
		//判断有无鼠标退出事件，若收到返回键，再回到正常的游戏逻辑，若收到退出，则退出游戏逻辑
		peekmessage(&m, EM_MOUSE);
		bool tag = 1;
		if (get_button_click(-SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT / 2 - 60, 140, 45, BROWN, 0x0B78E5, m, L"退出",1))
		{
			portray_exitpage();
			while (true)
			{
				getmessage(&m, EM_MOUSE);
				if (get_button_click(-120, 20, 90, 40, 0xCDEBFF, 0xE6F0FA, m, L"确认",0,BROWN))
				{
					tag = 0;
					break;
				}
				if (get_button_click(30, 20, 90, 40, 0xCDEBFF, 0xE6F0FA, m, L"返回",0,BROWN))
				{
					portray_gamepage(snake, obstacle, food);
					break;
				}
			}
		}
		flushmessage();
		if (!tag)
			break;
		
		//判断鼠标点击事件
		if (_kbhit())
		{
			ch = _getch();

			if (ch == 'w' || ch == 'W')
		
				snake.change_direction(NORTH);
			else if (ch == 's' || ch == 'S')
				snake.change_direction(SOUTH);
			else if(ch=='a'||ch=='A')
				snake.change_direction(WEST);
			else if (ch == 'd' || ch == 'D')
				snake.change_direction(EAST);

		}
		
		//蛇长度调整
		snake.adjust_length();

		//得分改变
		if (map[snake.head->x][snake.head->y] == FOOD_BURGER)
		{ 
			score += 2;
			food.num_burger--;
		}
		else if (map[snake.head->x][snake.head->y] == FOOD_CHICKEN)
		{
			score += 3;
			food.num_chicken--;
		}
		else if (map[snake.head->x][snake.head->y] == FOOD_FRUIT)
		{
			score += 4;
			food.num_fruit--;
		}

		//实时修改最佳分数
		best_score = score > best_score?score:best_score;

		//假如蛇头撞墙或者碰到身子，根据不同模式进行处理
		if (snake.is_dead())
		{
			if (mode != JUNIOR_MODE)
				hp--;
			if (hp)
			{
				if (mode == JUNIOR_MODE)
					obstacle.append();
				else if (mode == SENIOR_MODE)
					food.append();
				snake.init();
			}
			snake.current_direction = WEST;
			portray_gamepage(snake, obstacle, food);

			(void)_getch();
		}
		else
		{
			if (food.get_num_burger() + food.get_num_chicken() + food.get_num_fruit() == 0)
			{
				food.init(mode);
				portray_gamepage(snake,obstacle,food);
			}
			else
				update_scoreboard(food);
		}
	}
	//到了这里，说明游戏逻辑已经要结束了（无论是用户主动还是蛇死了），我们保存文件
	Game_Controller::update_record();
	Game_Controller::update_record(1);

}

//实时更新UI上的计分板
void Game_Controller::update_scoreboard(const Food& food)
{
	setfillcolor(0x33cccc); //游戏界面左侧背景色
	settextcolor(0x333333);
	//首先更新得分
	RECT rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 150,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 70 };
	
	wchar_t score_str[21];
	int2str(score, score_str);
	rect.left += 130; rect.top -= 22;  //暂时先别动
	rect.right += 15; rect.bottom -= 22;
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	//rect.right += 50;
	drawtext(score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 200,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 120 };

	wchar_t best_score_str[21];
	int2str(best_score, best_score_str);
	rect.left += 130; rect.top -= 22;  //暂时先别动
	rect.right += 15; rect.bottom -= 22;
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	//rect.right += 50;
	drawtext(best_score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);


	//然后更新食物
	rect = { -SCREEN_WIDTH / 2 + 130,35, -SCREEN_WIDTH / 2 + 260,65 };
	wchar_t buffer[16];
	buffer[0] = 'x';
	buffer[1] = ' ';
	buffer[2] = '\0';

	wchar_t str[10];
	int2str(food.get_num_burger(), str);
	wcscat_s(buffer, 10, str);
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	rect.top += 80;
	rect.bottom += 80;
	int2str(food.get_num_chicken(), str);
	buffer[2] = '\0';
	wcscat_s(buffer, 10, str);
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	rect.top += 80;
	rect.bottom += 80;
	int2str(food.get_num_fruit(), str);
	buffer[2] = '\0';
	wcscat_s(buffer, 10, str);
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);


}

//根据option的不同绘制排行榜页面或者历史记录页面，当且仅当收到返回键时退出
void Game_Controller::portray_toolspage(const int option)const
{
	settextcolor(BROWN);
	setfillcolor(0X6A6AFF);
	settextstyle(40, 0, _T("楷体"),0, 0, 1000, false, false, false);
	solidrectangle(-600, -400, 600, -400 + 134);
	RECT rect = { -200,-400 + 30,200,-400 + 104 };
	if (option == 2)
		drawtext(L"排行榜", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	else
		drawtext(L"历史记录(只读)", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);


	std::fstream ranks_file;
	if(option==2)
		ranks_file.open("ranks.log", std::ios::in|std::ios::_Nocreate);
	else
		ranks_file.open("records.log", std::ios::in | std::ios::_Nocreate);
	const wchar_t* mode_names[3] =
	{
		L"入门版:",L"进阶版:",L"高级版:"
	};
	const COLORREF colors[3] = { 0xE1E4FF,0XF5F0FF,0XE1E4FF};


	for (int i = 0; i < 3; i++)
	{
		settextstyle(35, 0, _T("楷体"), 0, 0, 1000, false, false, false);
		setfillcolor(colors[i]);
		solidrectangle(-600, -400 + 134 + 222 * i, 600, -400 + 134 + 222 * (i + 1));
		rect = { -560, -400 + 134 + 222 * i + 10,-440, -400 + 134 + 222 * i + 50 };
		drawtext(mode_names[i], &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

		int num_records = 0;
		ranks_file.seekg(int(double(159) *double( i)), std::ios::beg);
		ranks_file >> num_records;

		settextstyle(30, 0, _T("仿宋体"), 0, 0, 800, false, false, false);
		if (num_records == 0)
		{
			rect = { -200, -400 + 134 + 222 * i + 50,200,-400 + 134 + 222 * i + 222 - 50, };
			
			drawtext(L"暂无数据", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}
		else
		{
			int _score;
			char name[20];
			int year, month, day;
			for (int j = 0; j < num_records; j++)
			{
				ranks_file >> _score;
				ranks_file >> name;
				ranks_file >> year >> month >> day;
				rect = { -435,-400 + 134 + 222 * i + 74 *j,-345,-400 + 134 + 222 * i + 74 * j + 74 };
				drawtext(L"得分:", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left =-350;
				rect.right = -110;
				wchar_t buffer[9];
				int2str(_score, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = -110;
				rect.right = 10;
				drawtext(L"用户名:", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 15;
				rect.right = 255;
				wchar_t name_buffer[20] = { '\0' };
				for (int k = 0; name[k]; k++)
					name_buffer[k] = name[k];
				drawtext(name_buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 270;
				rect.right = 390;
				int2str(year, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 390;
				rect.right = 420;
				drawtext(L"-",&rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 420;
				rect.right = 480;
				int2str(month, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 480;
				rect.right = 510;
				drawtext(L"-", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 510;
				rect.right = 570;
				int2str(day, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
				
			}
		}

	}
	//返回按钮
	setfillcolor(0x238E6B);
	solidroundrect(490, 345, 590, 390, 20, 20);
	rect = { 490, 345, 590, 390 };
	settextstyle(25, 0, _T("仿宋"), 0, 0, 600, false, false, false);
	settextcolor(WHITE);
	drawtext(_T("返回"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	ExMessage m;
	
	bool tag = 1;
	while (true)
	{
		getmessage(&m, EM_MOUSE);
		if (m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x32CD9A);
			solidroundrect(490, 345, 590, 390, 20, 20);
			rect = { 490,345,590,390 };
			settextstyle(25, 0, _T("仿宋"), 0, 0, 600, false, false, false);
			settextcolor(WHITE);
			drawtext(_T("返回"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

			while (m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN)
				{
					tag = 0;
					break;
				}
				if (!(m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(0x238E6B);
					solidroundrect(490, 345, 590, 390, 20, 20);
					drawtext(_T("返回"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
					break;
				}
			}
			if (!tag)
				break;
		}
	}
}

//根据option的不同更新对应的记录文件
void Game_Controller::update_record(const int option)const
{
	std::fstream ranks_file;
	if(option==2)
		ranks_file.open("ranks.log", std::ios::in | std::ios::out, std::ios::_Nocreate);
	else
		ranks_file.open("records.log", std::ios::in | std::ios::out, std::ios::_Nocreate);

	ranks_file.seekg(int(double(159) *double( mode)), std::ios::beg);
	int num_ranks = 0, year, month, day;
	ranks_file >> num_ranks;
	if (num_ranks == 0)
	{
		ranks_file.seekg(int(double(159) * double(mode)), std::ios::beg);
		ranks_file << 1;
		ranks_file.seekg(int(double(159) * double(mode)+double(3)), std::ios::beg);
		ranks_file << score << " " << username << " ";
		time_t now = time(0);
		tm* ltm = localtime(&now);
		year = ltm->tm_year + 1900;
		month = ltm->tm_mon + 1;
		day = ltm->tm_mday;
		ranks_file << year<<" ";
		ranks_file << month<<" ";
		ranks_file << day<<" ";
	}

	else
	{
		UINT scores[3];
		//ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg);
		for (int i = 0; i < num_ranks; i++)
		{
			ranks_file.seekg(int(double(159) * double(mode) + 3), std::ios::beg);
			ranks_file.seekg(int(double(52) * double(i)), std::ios::cur);
			ranks_file >> scores[i];  //将记录存入程序，用于判断
		}

		int i = 0;
		for (i = 0; i < num_ranks; i++)
		{
			if (score > scores[i]||option==1)
			{
				int temy, temm, temd, temscore;
				char tempname[20];

				int pos;
				if (num_ranks == 3)
					pos = 1;
				else
					pos = num_ranks - 1;
				
				while (pos >= i)  //集体向后移动一位
				{
					ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg);
					ranks_file.seekg(int(double(52) * double(pos)), std::ios::cur);
					ranks_file >> temscore >> tempname >> temy >> temm >> temd;
					ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg); //寻找到下一行，进行删除操作
					ranks_file.seekg(int(double(52) * double(pos)+52), std::ios::cur);
					ranks_file << "                                                  "; //删除完毕，开始移动
					//
					ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg); 
					ranks_file.seekg(int(double(52) * double(pos) + 52), std::ios::cur);

					ranks_file <<temscore << " " << tempname << " ";
					ranks_file << temy << " ";
					ranks_file << temm << " ";
					ranks_file << temd << " ";
					pos--;

				}
				//在后续的都移动完毕后，我们将第i行抹去，换上新记录
				ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg);
				ranks_file.seekg(int(double(52) * double(i)), std::ios::cur);
				ranks_file << "                                                  "; //删除完毕，开始移动
				ranks_file.seekg(int(double(159) * double(mode) + 3), std::ios::beg);
				ranks_file.seekg(int(double(52) * double(i) ), std::ios::cur);
				ranks_file << score << " " << username << " ";
				time_t now = time(0);
				tm* ltm = localtime(&now);
				year = ltm->tm_year + 1900;
				month = ltm->tm_mon + 1;
				day = ltm->tm_mday;
				ranks_file << year << " ";
				ranks_file << month << " ";
				ranks_file << day << " ";

				ranks_file.seekg(int(double(159) * double(mode)), std::ios::beg); //更新数量
				num_ranks += (num_ranks != 3);
				ranks_file << num_ranks;
				break;

			}
		}
		if (i == num_ranks && num_ranks < 3)
		{
			ranks_file.seekg(int(double(159) * double(mode) + 3), std::ios::beg);
			ranks_file.seekg(int(double(52) * double(i)), std::ios::cur);
			ranks_file << score << " " << username << " ";
			time_t now = time(0);
			tm* ltm = localtime(&now);
			year = ltm->tm_year + 1900;
			month = ltm->tm_mon + 1;
			day = ltm->tm_mday;
			ranks_file << year << " ";
			ranks_file << month << " ";
			ranks_file << day << " ";

			ranks_file.seekg(int(double(159) * double(mode)), std::ios::beg); //更新数量
			num_ranks += (num_ranks != 3);
			ranks_file << num_ranks ;
		}


		

	}
	ranks_file.close();

}

//获取合法的用户名
void Game_Controller::set_username()
{
	setfillcolor(0xCDEBFF);
	solidroundrect(-300, -200, 300, 200, ROUND_ANGLE, ROUND_ANGLE);

	RECT rect = { -270,-210,270,0 };
	settextcolor(BROWN);
	drawtext(_T("请输入用户名(1-7个英文)"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	setfillcolor(0xDCF8FF);
	solidroundrect(-200, 0, 200, 90, ROUND_ANGLE, ROUND_ANGLE);

	solidroundrect(-70, 120, 70, 190, ROUND_ANGLE, ROUND_ANGLE);
	rect = { -70,120,70,190 };
	drawtext(_T("确认"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	wchar_t name[8] = { '\0' };
	int length = 0, pointer = 0;
	char ch;
	ExMessage m;
	
	rect = { -200, 0, 200, 90 };
	while (true)
	{
		settextcolor(BROWN);
		peekmessage(&m, EM_MOUSE);
		if (get_button_click(-70, 120, 140, 70, 0XDCF8FF, WHITE, m, _T("确认"), true,BROWN))
		{
			if (length == 0)
			{
				settextcolor(BROWN);
				drawtext(_T("不合法"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
				Sleep(1000);
				solidroundrect(-200, 0, 200, 90, ROUND_ANGLE, ROUND_ANGLE);

			}
			else
				break;
		};
		if (_kbhit())
		{
			ch = _getch();
			if ((ch >= 'a' && ch <= 'z') || (ch <= 'Z' && ch>='A') || ch == '_')
			{
				if (length < 7)
				{
					length++;
					name[pointer++] = ch;

					drawtext(name, &rect, DT_VCENTER  | DT_LEFT);
				}
				
			}
			else if (ch == '\b'&&length>0)
			{
				length--;
				name[--pointer] = '\0';
				setfillcolor(0xDCF8FF);
				solidroundrect(-200, 0, 200, 90, ROUND_ANGLE, ROUND_ANGLE);
				drawtext(name, &rect, DT_VCENTER | DT_LEFT);
			}
		}
	}
	for (int i = 0; i < 8; i++)
		username[i] = static_cast<char>(name[i]);


}

Game_Controller::~Game_Controller()
{
	if (map)
	{
		for (int i = 0; i <= MAP_WIDTH; i++)
			delete[] map[i];
		delete[] map;
	}
}