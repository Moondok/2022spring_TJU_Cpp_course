
#include<graphics.h>
#include"Gluttonous_Snake.h"


int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	
	Game_Controller Controller; //这个时候，地图的空间就开辟好了
	while (true)
	{
		PlaySound(_T("audio/bgm1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  //放音乐
		Controller.portray_firstpage();                                               //绘制首页
		int option = Controller.get_option();                                     //获取选项
		if (option == 3)                                //选择退出游戏
			break;

		if (option == 0)                                //选择新游戏
		{
			Controller.portray_rulespage();                
			int mode = Controller.get_mode();
			if (!(mode + 1))
				continue;
			Controller.set_mode(mode);
			Controller.set_score(0);
			PlaySound(NULL, NULL, SND_FILENAME );
			Controller.enter_game(); //这里，用户胜利/输/主动退出，这里是唯一一个出口，返回while循环的开头
		}
		else if (option == 2)                   //选择查看排行榜
			Controller.portray_toolspage();
			
		else if(option==1)
			Controller.portray_toolspage(option);   //选择查看历史记录
	}
	closegraph();
	return 0;
}