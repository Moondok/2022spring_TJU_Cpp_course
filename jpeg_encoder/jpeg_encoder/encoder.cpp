#include<iostream>
#include"encoder.h"
#include"PicReader.h"

/**********************************
功能:完成处理一张图片的全过程
参数:pic_name:图像路径
************************************/
void encoder::Pipeline(const char* pic_name)
{
	MakeFile(pic_name);
	PicReader imreader;
	imreader.readPic(pic_name);
	imreader.getData(pic, w, h);
	WriteHeader();

	RGB2YUV();
	DownSampling();

	short pre_DC_Y = 0;
	short pre_Dc_Cr = 0;
	short pre_Dc_Cb = 0;

	BYTE content = 0;
	int contentpos = 7;
	for (UINT i = 0; i < h / MCU_SIZE; i++) //高 ,高和宽的顺序不能反！
		for (UINT j = 0; j < w / MCU_SIZE; j++)
		{
			short MCU_Y[4][64] = { 0, };
			short MCU_Cr[64] = { 0, };
			short MCU_Cb[64] = { 0, };
			short Luminance_ZigZag[4][64] = { 0, };
			short Chrominancer_ZigZag[64] = { 0, };
			short Chrominanceb_ZigZag[64] = { 0, };

			DCT(i * MCU_SIZE, j * MCU_SIZE, MCU_Y);
			Quantization(MCU_Y);
			DCT(i * MCU_SIZE / 2, j * MCU_SIZE / 2, MCU_Cr, 0);
			Quantization(MCU_Cr);
			DCT(i * MCU_SIZE / 2, j * MCU_SIZE / 2, MCU_Cb, 1);

			Quantization(MCU_Cb);
			ZigZagReshape(MCU_Y, Luminance_ZigZag);
			ZigZagReshape(MCU_Cr, Chrominancer_ZigZag);
			ZigZagReshape(MCU_Cb, Chrominanceb_ZigZag);

			RestoreMCU(pre_DC_Y, pre_Dc_Cr, pre_Dc_Cb, Luminance_ZigZag, Chrominancer_ZigZag, Chrominanceb_ZigZag, content, contentpos);
		}

	char ch = static_cast<char>(0x00);
	if (contentpos != 7)  //说明还有一个字节未写入文件
	{
		outfile.write((char*)&content, sizeof(char));
		if (content == 0xff) //特殊处理
			outfile.write((char*)&ch, sizeof(char));
	}
	outfile.write((char*)&END_MARKER, sizeof(short));
	return;
}


/****************************
功能:实现RGB三通道向YUV三通道转换
******************************/
void encoder::RGB2YUV()
{
	//组件YUV三张表
	Ymap = new(nothrow) char* [h];
	Crmap = new(nothrow) char* [h];
	Cbmap = new(nothrow) char* [h];
	if (Ymap == NULL||Crmap==NULL||Cbmap==NULL)
	{
		cerr << "Something Wrong Happens!" << endl;
		exit(EXIT_FAILURE);
	}
	for (UINT i = 0; i < h; i++)
	{
		Ymap[i] = new(nothrow) char[w];
		Crmap[i] = new(nothrow) char[w];
		Cbmap[i] = new(nothrow) char[w];
		if (Crmap[i] == NULL||Cbmap[i]==NULL||Ymap[i]==NULL)
		{
			cerr << "Something Wrong Happens!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	for (UINT i = 0; i < h; i++)
		for (UINT j = 0; j < w; j++)
		{
			Ymap[i][j] = (char)(pic[(i * w + j) * 4] * 0.299 + pic[(i * w + j) * 4 + 1] * 0.587 + pic[(i * w + j) * 4 + 2] * 0.114 - 128);
			Cbmap[i][j] = (char)(pic[(i * w + j) * 4] * (-0.1687) + pic[(i * w + j) * 4 + 1] * (-0.3313) + pic[(i * w + j) * 4 + 2] * 0.500);
			Crmap[i][j] = (char)(pic[(i * w + j) * 4] * (0.500) + pic[(i * w + j) * 4 + 1] * (-0.4187) - pic[(i * w + j) * 4 + 2] * 0.0813);
		}
}


/***************************
功能:实现对色度分量的降采样（2x2->1)
****************************/
void encoder::DownSampling()
{
	Crmap_DownSamed = new (nothrow)char* [h / 2];
	if (Crmap_DownSamed == NULL)
	{
		cerr << "Something Wrong happens!" << endl;
		exit(EXIT_FAILURE);
	}
	Cbmap_DownSamed = new (nothrow)char* [h / 2];
	if (Cbmap_DownSamed == NULL)
	{
		cerr << "Something Wrong happens!" << endl;
		exit(EXIT_FAILURE);
	}
	for (UINT i = 0; i < h / 2; i++)
	{
		Crmap_DownSamed[i] = new(nothrow) char[w / 2];
		Cbmap_DownSamed[i] = new(nothrow) char[w / 2];
		if (Crmap_DownSamed[i] == NULL || Cbmap_DownSamed[i] == NULL)
		{
			cerr << "Something Wrong happens!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	for (UINT i = 0; i < h / 2; i++)
		for (UINT j = 0; j < w / 2; j++)
		{
			Crmap_DownSamed[i][j] = (Crmap[2 * i][2 * j] + Crmap[2 * i][2 * j + 1] + Crmap[2 * i + 1][2 * j] + Crmap[2 * i + 1][2 * j + 1]) / 4;
			Cbmap_DownSamed[i][j] = (Cbmap[2 * i][2 * j] + Cbmap[2 * i][2 * j + 1] + Cbmap[2 * i + 1][2 * j] + Cbmap[2 * i + 1][2 * j + 1]) / 4;
		}
}


/******************************************
功能:实现对一个MCU内亮度分量的离散余弦变换
参数:base_x: 该16x16小块在原始图像上的纵坐标
	 base_y: 该16x16小块在原始图像上的横坐标
	 MCU_Y:  存储变换后的数据
*******************************************/
void encoder::DCT(const int base_x, const int base_y, short MCU_Y[4][64])//base_x,base_y是一个MCU左上角的坐标
{
	int block_x = base_x;
	int block_y = base_y;
	for (int k = 1; k < 5; k++)
	{
		for (int u = 0; u < BLOCK_SIZE; u++)
		{
			for (int v = 0; v < BLOCK_SIZE; v++)
			{
				double alphau = (u == 0) ? 1.0 / sqrt(8) : 0.5;
				double alphav = (v == 0) ? 1.0 / sqrt(8) : 0.5;
				double tmp = 0;
				for (int x = 0; x < BLOCK_SIZE; x++)
					for (int y = 0; y < BLOCK_SIZE; y++)
						tmp += short(Ymap[block_x + x][block_y + y] * cos((2.0 * x + 1) / 16 * u * PI) * cos((2.0 * y + 1) / 16 * v * PI));

				MCU_Y[k - 1][u * BLOCK_SIZE + v] = static_cast<short>(alphau * alphav * tmp);
			}

		}
		block_x = base_x + (k / 2) * BLOCK_SIZE;
		block_y = base_y + (k % 2) * BLOCK_SIZE;
	}
}


/******************************************
功能:实现对一个MCU内一个色度分量的离散余弦变换
参数:base_x: 该16x16小块在原始图像上的纵坐标
	 base_y: 该16x16小块在原始图像上的横坐标
	 MCU_C:  存储变换后的数据
*******************************************/
void encoder::DCT(const int base_x, const int base_y, short MCU_C[64], const bool tag)
{
	for (int u = 0; u < BLOCK_SIZE; u++)
		for (int v = 0; v < BLOCK_SIZE; v++)
		{
			double alphau = (u == 0) ? 1 / sqrt(8.0) : 0.5;
			double alphav = (v == 0) ? 1 / sqrt(8.0) : 0.5;
			double tmp = 0;
			for (int x = 0; x < BLOCK_SIZE; x++)
				for (int y = 0; y < BLOCK_SIZE; y++)
				{
					if (tag == 0)
						tmp += (Cbmap_DownSamed[base_x + x][base_y + y] * cos((2.0 * x + 1) / 16.0 * u * PI) * cos((2.0 * y + 1) / 16.0 * v * PI));
					else if (tag == 1)
						tmp += (Crmap_DownSamed[base_x + x][base_y + y] * cos((2.0 * x + 1) / 16.0 * u * PI) * cos((2.0 * y + 1) / 16.0 * v * PI));
				}

			MCU_C[u * BLOCK_SIZE + v] = static_cast<short>(alphau * alphav * tmp);
		}
}


/******************************************
功能:实现对一个MCU内亮度分量的量化
参数: MCU_Y:  离散余弦变换后的亮度数据
*******************************************/
void encoder::Quantization(short MCU_Y[4][64])
{
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 64; i++)
			MCU_Y[k][i] /= Luminance_Quant_Table[i];
}

/******************************************
功能:实现对一个MCU内色度分量的量化
参数: MCU_Y:  离散余弦变换后的亮度数据
*******************************************/
void encoder::Quantization(short MCU_C[64])
{
	for (int i = 0; i < 64; i++)
		MCU_C[i] /= Chrominance_Quant_Table[i];
}

/******************************************
功能:实现对一个MCU内亮度分量的ZigZag排序
参数: MCU_Y:  量化后的亮度数据，
	  ZigZagSequence:重新排序后的亮度数据
*******************************************/
void encoder::ZigZagReshape(const short MCU_Y[4][64], short ZigZagSequence[4][64])
{
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 64; i++)
			ZigZagSequence[k][ZigZag_Table[i]] = MCU_Y[k][i];
}

/******************************************
功能:实现对一个MCU内色度分量的ZigZag排序
参数: MCU_C:  量化后的色度数据，
	  ZigZagSequence:重新排序后的色度数据
*******************************************/
void encoder::ZigZagReshape(const short MCU_C[64], short ZigZagSequence[64])
{
	for (int i = 0; i < 64; i++)
		ZigZagSequence[ZigZag_Table[i]] = MCU_C[i];
}

/***************************************
功能:初始化哈夫曼表
参数:EstablishedLengthTable:官方给出的长度推荐表
	 EstablishedValueTable:官方给出的对应值
	 HT:保存结果
******************************************/
void encoder::InitHuffmanTable(const BYTE* EstablishedLengthTable, const BYTE* EstablishedValueTable, unit* HT)
{
	int pos = 0;
	int value = 0;
	for (int i = 1; i <= HuffmanTreeHeight; i++)
	{
		for (int j = 0; j < EstablishedLengthTable[i - 1]; j++)
		{   //这里类似桶排序，下标即是值
			HT[EstablishedValueTable[pos]].length = i;
			HT[EstablishedValueTable[pos]].value = value;
			//这里的value其实是编码，下标是源值
			pos++;  //源值在value表中的位置增加
			value++;  //编码长度相等的值按顺序加1即可，是Canonical Huffman coding的性质
		}
		value = value << 1;  //去往下一层哈夫曼树，码字长度加1，对应到int型上，就是左移。
	}
}

/**************************************
功能:向文件中写入一个MCU
参数:pre_DC_Y:上一个block的Y的直流分量
	 pre_Dc_Cr:上一个block的Cr的直流分量
	 pre_Dc_Cb:上一个block的Cb的直流分量
	 MCU_Y: 该MCU内四个亮度分量的数据
	 MCU_Cr:该MCU内Cr亮度分量的数据
	 MCU_Cb:该MCU内Cb亮度分量的数据
	 content:待写入字节的引用
	 contentpos:待写入字节当前空余位置的引用
*******************************************/
void encoder::RestoreMCU(short& pre_DC_Y, short& pre_Dc_Cr, short& pre_Dc_Cb, const short MCU_Y[4][64], const short MCU_Cr[64], const short MCU_Cb[64], BYTE& content, int& contentpos)
{
	//存入一个MCU,对应原矩阵中16x16的方格，由4个8x8的Y分量和2个降采样的Cr,Cb变量组成
	for (int k = 0; k < 4; k++)
		RestoreBlock(pre_DC_Y, MCU_Y[k], content, contentpos, 0);

	RestoreBlock(pre_Dc_Cr, MCU_Cr, content, contentpos, 1);
	RestoreBlock(pre_Dc_Cb, MCU_Cb, content, contentpos, 1);

}

/**************************************
功能:向文件中写入一个block
参数:pre_DC:上一个block的直流分量
	 MCU_: 该block内一个分量的数据
	 content:待写入字节的引用
	 contentpos:待写入字节当前空余位置的引用
	 tag：用于判断这个block是亮度还是色度的标志
*******************************************/
void encoder::RestoreBlock(short& pre_DC, const short MCU_[64], BYTE& content, int& contentpos,const bool tag)
{
	unit result[128];
	int pos = 0;
	int value = 0; //作为实际值，在对AC编码中使用
	short gap = MCU_[0] - pre_DC;
	pre_DC = MCU_[0];
	if (gap == 0)
		result[pos++] = (tag ? Chrominance_Dc_HT[gap] : Luminance_Dc_HT[gap]);
	//后面的特殊编码不需要！

	else
	{
		unit re = SpecialStandardEncoding(gap);
		result[pos++] = tag ? Chrominance_Dc_HT[re.length] : Luminance_Dc_HT[re.length];
		result[pos++] = re;
	}

	//再存AC分量
	for (int i = 1; i < 64; i++)
	{
		int j = 0;   //一个三元组中第一个元素:0的个数
		for (j = 0; i + j < 64; j++)
			if (MCU_[i + j] != 0)
				break;

		//j个0
		//截至到这里，有这么几种情况:i+j==64->存入EOB即可； i+j<64，说明前面有j/16和16个0的小块以及(j\%16)个0加上一个非0值
		if (i + j == 64)
		{
			result[pos++] = tag ? Chrominance_Ac_HT[EOB] : Luminance_Ac_HT[EOB];
			break;
		}
		else
		{
			for (int m = 0; m < j / 16; m++) //这都是16个0的块
				result[pos++] = tag ? Chrominance_Ac_HT[0xF0] : Luminance_Ac_HT[0xF0];
			result[pos + 1] = SpecialStandardEncoding(MCU_[i + j]);
			value = result[pos + 1].length;
			value = value | ((j % 16) << 4);
			result[pos + 0] = tag ? Chrominance_Ac_HT[value] : Luminance_Ac_HT[value];
			pos = pos + 2;
			i += j;
		}
	}

	UINT cnt = pos;
	//此时一个block已经全部转移到了unit中，是时候开始写入文件了，写入的长度为pos
	UINT mask[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048 ,4096,8192 }; //掩膜，用于提取特定位的比特位

	int lengthpos = 0;
	int realvalue = 0;
	const BYTE ch = 0x00;
	for (UINT i = 0; i < cnt; i++)
	{
		lengthpos = result[i].length;
		realvalue = result[i].value;
		for (int j = lengthpos - 1; j >= 0; j--)
		{
			int tmp = realvalue & mask[j];
			if (tmp != 0) //这一位是1
				content |= mask[contentpos];
			contentpos--;
			if (contentpos < 0) //该字节填充完毕
			{
				outfile.write((char*)&content, sizeof(char));
				//重置字节位
				if (content == 0xff) //特殊处理
					outfile.write((char*)&ch, sizeof(char));
				content = 0;
				contentpos = 7;
			}

		}
	}
}

/**************************************
功能:实现对一个值进行特殊编码(3->11  -3:00)
参数:待编码的值
************************************/
unit encoder::SpecialStandardEncoding(const short& value)
{
	short tem = value;
	unit re;

	int length = 1;
	while (tem != 1 && tem != -1)
	{
		tem /= 2;
		length++;
	}
	tem = value;//重置
	re.value = (tem > 0) ? tem : ((1 << length) + value - 1);  //负数取反
	re.length = length;
	return re;

}

/******************************
功能:创建一个新文件
参数:原始文件路径
*******************************/
void encoder::MakeFile(const char* pic_name)
{
	char name[100] = { '\0' };
	int i = 0;
	for (i = 0;; i++)
	{
		if (pic_name[i] == '.')
			break;
		name[i] = pic_name[i];
	}
	//为了不写define no warnings
	name[i++] = '.';
	name[i++] = 'j';
	name[i++] = 'p';
	name[i++] = 'e';
	name[i++] = 'g';

	outfile.open(name, ios::out | ios::binary);
	if (outfile.is_open() == 0)
	{
		cerr << "Fail to compress!" << endl;
		exit(EXIT_FAILURE);
	}
}

/**************************************
功能:在创建的jpeg文件开始处写入一些标头
***************************************/
void encoder::WriteHeader()
{
	outfile.write((char*)&SOI_MARKER, sizeof(short));

	outfile.write((char*)&APPO_MARKER, sizeof(short));
	outfile.write((char*)&APP0_SEGMENT_LENGTH, sizeof(short));
	outfile.write("JFIF", sizeof(char) * 5);
	outfile << static_cast<char>(1);
	outfile << static_cast<char>(1);
	outfile << static_cast<char>(0);
	outfile.write((char*)&DENSITY, sizeof(short));
	outfile.write((char*)&DENSITY, sizeof(short));
	outfile << static_cast<char>(0);
	outfile << static_cast<char>(0);

	outfile.write((char*)&DQT_MARKER, sizeof(short));
	outfile.write((char*)&DQT_SEGMENT_LENGTH, sizeof(short));
	outfile << static_cast<char>(0);
	outfile.write((char*)Luminance_QT, sizeof(char) * 64);
	outfile << static_cast<char>(1);
	outfile.write((char*)Chrominance_QT, sizeof(char) * 64);

	outfile.write((char*)&SOFO_MARKER, sizeof(short));
	outfile.write((char*)&SOFO_SEGMENT_LENGTH, sizeof(short));
	outfile << static_cast<char>(8);
	//写入图片长宽
	short tmp = turnover(h);
	outfile.write((char*)&tmp, sizeof(short));
	tmp = turnover(w);
	outfile.write((char*)&tmp, sizeof(short));
	outfile << static_cast<char>(3);

	outfile << static_cast<char>(1);  //Y
	outfile << static_cast<char>(0x22);  //隔点采样！
	outfile << static_cast<char>(0);

	outfile << static_cast<char>(2);
	outfile << static_cast<char>(0x11);
	outfile << static_cast<char>(1);

	outfile << static_cast<char>(3);
	outfile << static_cast<char>(0x11);
	outfile << static_cast<char>(1);

	//DHT
	outfile.write((char*)&DHT_MARKER, sizeof(short));
	outfile.write((char*)&DHT_LENGTH, sizeof(short));
	outfile << static_cast<char>(0);

	outfile.write((char*)LuminanceDC_HT_Length, sizeof(LuminanceDC_HT_Length));
	outfile.write((char*)LuminanceDC_HT_Value, sizeof(LuminanceDC_HT_Value));

	outfile << static_cast<char>(0x10);
	outfile.write((char*)LuminanceAC_HT_Length, sizeof(LuminanceAC_HT_Length));
	outfile.write((char*)LuminanceAC_HT_Value, sizeof(LuminanceAC_HT_Value));

	outfile << static_cast<char>(0x01);
	outfile.write((char*)ChrominanceDC_HT_Length, sizeof(ChrominanceDC_HT_Length));
	outfile.write((char*)ChrominanceDC_HT_Value, sizeof(ChrominanceDC_HT_Value));
	outfile << static_cast<char>(0x11);
	outfile.write((char*)ChrominanceAC_HT_Length, sizeof(ChrominanceAC_HT_Length));
	outfile.write((char*)ChrominanceAC_HT_Value, sizeof(ChrominanceAC_HT_Value));


	outfile.write((char*)&SOS_MARKER, sizeof(short));
	outfile.write((char*)&SOS_LENGTH, sizeof(short));
	outfile << static_cast<char>(3);

	outfile << static_cast<char>(1);
	outfile << static_cast<char>(0);
	outfile << static_cast<char>(2);
	outfile << static_cast<char>(0x11);

	outfile << static_cast<char>(3);
	outfile << static_cast<char>(0x11);

	outfile << static_cast<char>(0);
	outfile << static_cast<char>(0x3f);
	outfile << static_cast<char>(0);

}

/*****************************
功能:将二字节数据高低位字节转换
参数:待转换数据
*********************************/
short encoder::turnover(short n)
{
	n = ((n << 8) & short(0xFF00)) | ((n >> 8) & short(0x00FF));
	return n;
}

/********************************
功能:以ZigZag的方式将量化表排序从而存入文件头
********************************/
void encoder::InitQuantTable()
{
	for (int i = 0; i < 64; i++)
	{
		Luminance_QT[ZigZag_Table[i]] = Luminance_Quant_Table[i];
		Chrominance_QT[ZigZag_Table[i]] = Chrominance_Quant_Table[i];
	}
}

encoder::encoder(UINT width, UINT height) : w(width), h(height)
{
	InitHuffmanTable(LuminanceDC_HT_Length, LuminanceDC_HT_Value, Luminance_Dc_HT);
	InitHuffmanTable(LuminanceAC_HT_Length, LuminanceAC_HT_Value, Luminance_Ac_HT);
	InitHuffmanTable(ChrominanceDC_HT_Length, ChrominanceDC_HT_Value, Chrominance_Dc_HT);
	InitHuffmanTable(ChrominanceAC_HT_Length, ChrominanceAC_HT_Value, Chrominance_Ac_HT);
	InitQuantTable();
};

encoder::~encoder()
{
	delete pic;
	for (unsigned int i = 0; i < h; i++)
	{
		delete[]Ymap[i];
		delete[]Crmap[i];
		delete[]Cbmap[i];
		if (i < h / 2)
		{
			delete[]Crmap_DownSamed[i];
			delete[]Cbmap_DownSamed[i];
		}
	}
	delete[] Ymap;
	delete[] Crmap;
	delete[] Cbmap;
	delete[] Crmap_DownSamed;
	delete[] Cbmap_DownSamed;
	if (outfile.is_open())
		outfile.close();
	cout << "Done!" << endl;
}