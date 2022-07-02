#include"Gluttonous_Snake.h"

extern unsigned char ** map;

//*********Snake*********//
//初始化一条新蛇
void Snake::init()
{
	if (body != NULL)
		Snake::destroy();  
	body = new(std::nothrow) segment;
	if (body == NULL)
		exit(EXIT_FAILURE);
	segment* track = body;
	for (int i = 0; i < 5; i++)
	{
		segment* newnode = new(std::nothrow) segment;
		if (newnode == NULL)
			exit(EXIT_FAILURE);
		newnode->x = MAP_WIDTH/2+i-1;   //一个20*20的块为一个节  21,22,23,24,25
		newnode->y = MAP_HEIGHT/2;
		newnode->former = track;
		if (i == 0)
			head = newnode;  //初始化头
		else if (i == 4)
			tail= newnode;  //初始化尾巴

		map[newnode->x][newnode->y] = SNAKE_BODY;
		track->next = newnode;
		track = newnode;
	}
	map[MAP_WIDTH / 2 - 1][MAP_HEIGHT / 2] = SNAKE_HEAD;
	length = 5;
}

//改变蛇的行进方向
void Snake::change_direction(const int new_direction)
{
	current_direction = new_direction;
}

//添加蛇头
void Snake::append_head()
{
	//设置新的蛇头
	segment* newhead = new(std::nothrow) segment;
	if (newhead == NULL)
		exit(EXIT_FAILURE);
	if (current_direction == NORTH)
	{
		newhead->x = head->x;
		newhead->y = head->y - 1;
	}
	else if (current_direction == SOUTH)
	{
		newhead->x = head->x;
		newhead->y = head->y + 1;
	}
	else if (current_direction == WEST)
	{
		newhead->x = head->x-1;
		newhead->y = head->y;
	}
	else
	{
		newhead->x = head->x + 1;
		newhead->y = head->y;
	}
	//改换原蛇头的颜色
	int x = 20 * (head->x - 1) + 300 - SCREEN_WIDTH / 2, y = 20 * (head->y - 1) - SCREEN_HEIGHT / 2;
	setfillcolor(BROWN);
	fillrectangle(x, y, x + 20, y + 20);
	map[head->x][head->y] = SNAKE_BODY;  //旧蛇头没关系
	
	
	//画上新蛇头的颜色
	if ((map[newhead->x][newhead->y] == FOOD_BURGER || map[newhead->x][newhead->y] == FOOD_CHICKEN || map[newhead->x][newhead->y] == FOOD_FRUIT))
		PlaySound(_T("audio/eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
	x= 20 * (newhead->x - 1) + 300 - SCREEN_WIDTH / 2, y = 20 * (newhead->y - 1) - SCREEN_HEIGHT / 2;
	setfillcolor(0X2f6b55);
	fillrectangle(x, y, x + 20, y + 20);
	
	//内部链表进行修改
	body->next = newhead;
	newhead->former = body;
	newhead->next = head;
	head->former = newhead;
	head = newhead;  //蛇头交接
	
	length++;
}

//删去蛇尾
void Snake::delete_tail()
{
	segment* oldtail = tail;
	int x= x = 20 * (oldtail->x - 1) + 300 - SCREEN_WIDTH / 2, y = 20 * (oldtail->y - 1) - SCREEN_HEIGHT / 2;
	setfillcolor(0X8FF6FF);
	fillrectangle(x, y, x + 20, y + 20);
	map[tail->x][tail->y] = 0;  //重新设置map
	tail = tail->former;
	delete tail->next;
	tail->next = NULL;
	length--;
	
}

//调整蛇的长度
void Snake::adjust_length()
{
	Snake::append_head();
	if (!(map[head->x][head->y] == FOOD_BURGER || map[head->x][head->y] == FOOD_CHICKEN || map[head->x][head->y] == FOOD_FRUIT|| 
		  map[head->x][head->y] == OBSTACLE|| map[head->x][head->y]==SNAKE_BODY))
	{
		Snake::delete_tail();
		
	}
	Sleep(150);
}

//判定一条蛇是否已经死亡
bool Snake::is_dead()
{
	if (map[head->x][head->y] == OBSTACLE || map[head->x][head->y] == SNAKE_BODY)
	{
		return 1;
	}
	else
		map[head->x][head->y] = SNAKE_HEAD;  //只有蛇活着这种情况才在地图上标出蛇头

	return 0;
	
}

//销毁一条蛇的内存开销
void Snake::destroy()
{
	segment* track_former = head;
	if (track_former == NULL)
		return;
	segment* track_latter = head->next;
	while (track_latter->next)
	{
		delete track_former;
		track_former = track_latter;
		track_latter = track_latter->next;
	}
	delete track_former;

	head = body = NULL;
}

Snake::~Snake()
{
	if (body)
		Snake::destroy();
}

//******* Obstacle*******//
//初始化外墙
void Obstacle::init()
{
	for (int i = 1; i <= MAP_WIDTH; i++)
		map[i][1] = map[i][MAP_HEIGHT] = OBSTACLE;

	for (int j = 1; j <= MAP_HEIGHT; j++)
		map[1][j] = map[MAP_WIDTH][j] = OBSTACLE;

}

//将蛇的身体添加为外墙
void Obstacle::append()
{
	for (int i = 1; i <= MAP_WIDTH; i++)
		for (int j = 1; j <=MAP_HEIGHT; j++)
			if (map[i][j] == SNAKE_HEAD || map[i][j] == SNAKE_BODY)
				map[i][j] = OBSTACLE;
}


//*******Food*****/
//初始化食物
void Food::init(const int mode)
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		int x = rand() % MAP_WIDTH + 1;
		int y = rand() % MAP_HEIGHT + 1;
		if (!(map[x][y]-SNAKE_BODY)||!(map[x][y]-OBSTACLE)||!(map[x][y]-SNAKE_HEAD))
			i--;
		else
		{
			
			int seed = rand() % 3+1;
			if (seed == 1)
			{
				map[x][y] = FOOD_BURGER;
				num_burger++;
			}
			else if (seed == 2)
			{
				map[x][y] = FOOD_CHICKEN;
				num_chicken++;
			}
			else
			{
				map[x][y] = FOOD_FRUIT;
				num_fruit++;
			}
		}
	}
}

//将蛇的身体添加为食物
void Food::append()
{
	for (int i = 1; i <= MAP_WIDTH; i++)
		for (int j = 1; j <= MAP_HEIGHT; j++)
			if (map[i][j] == SNAKE_HEAD || map[i][j] == SNAKE_BODY)
			{
				int seed = rand() % 3 + 1;
				switch (seed)
				{
					case 1:
						map[i][j] = FOOD_BURGER;
						num_burger++;
						break;
					case 2:
						map[i][j] = FOOD_CHICKEN;
						num_chicken++;
						break;
					case 3:
						map[i][j] = FOOD_FRUIT;
						num_fruit++;
						break;
					default:
						break;
				}
			}	
}

