#include<iostream>
#include"encoder.h"
#include"PicReader.h"

int main(int argc, char* argv[])
{
	if (GetCommand(argc, argv))
		HandleCommand(argv);
	return 0;
}


/***************************************
功能:获取用户在命令行中输入的指令，并判断其合法性
参数:argc:主函数中参数数量
	 argv:主函数中参数列表
返回值:主函数参数合法性
*************************************/
bool GetCommand(int argc, char* argv[])
{
	bool re = false;
	if (argc != 3)
	{
		cerr << "The number of parameters is wrong!" << endl;
		re = false;
	}

	else if (!strcmp("-read", argv[1]) || !(strcmp("-compress", argv[1])))
	{
		fstream infile;
		infile.open(argv[2], ios::in);
		if (infile.is_open() == 0)
		{
			cerr << "Fail to open target file " << argv[2] << " !" << endl;
			re = false;
		}
		else
		{
			infile.close();//假如能打开，证明存在，调用框架即可，所以关掉这个文件
			re = true;

		}
	}
	else
		cerr << "the Command is not in the command list!\nCommand List:\n -compress\n -read" << endl;
	return re;
}


/***********************************
功能:处理用户输入的命令
参数: argv:主函数中用户输入的命令
***************************************/
void HandleCommand(char* argv[])
{
	if (!strcmp("-compress", argv[1]))
	{
		encoder jpeg_encoder;
		jpeg_encoder.Pipeline(argv[2]);
	}
	else if (!strcmp("-read", argv[1]))
	{
		PicReader reader;
		BYTE* data = nullptr;
		UINT x, y;
		reader.readPic(argv[2]);
		reader.getData(data, x, y);
		reader.showPic(data, x, y);
	}
}