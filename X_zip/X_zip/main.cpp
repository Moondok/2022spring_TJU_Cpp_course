#include<iostream>
#include<time.h>
#include<sstream>
#include"X_zip.h"
using namespace std;

//带参主函数，第二个参数是指令(压缩/解压),第三个是输入文件，第四个是目标输出文件
int main(int argc,char * argv[])
{
	cout << "X_zipper Version --0.1  Author: Kaixu Chen" << endl;

	//判定参数数量
	if (argc != 4)
	{
		cerr << "Please make sure the number of parameters is correct!" << endl;
		return -1;
	}

	//判定第二个参数是不是解压或者压缩命令
	if (strcmp(argv[1], "zip") && strcmp(argv[1], "unzip"))
	{
		cerr << "Unknown parameters!\nCommand List:\nzip\t unzip" << endl;
		return -1;
	}

	//尝试打开目标文件(待压缩/解压）
	ifstream infile;
	infile.open(argv[2], ios::binary);
	if (infile.is_open() == 0)
	{
		cout << "Fail to open the input file!" << endl;
		return -1;
	}
	clock_t finish; 

	if (strcmp(argv[1], "zip") == 0)
		Zip_file(infile, argv[3]);
	else if (strcmp(argv[1], "unzip") == 0)
		Unzip_file(infile,argv[3]);

	finish = clock();
	cout << "Execution time: "<<double(finish) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}

//压缩选项对应的函数
void Zip_file(ifstream& infile,const char * output_name)
{
	ofstream outfile;
	outfile.open(output_name, ios::out);
	if (outfile.is_open() == 0)
	{
		cerr << "Fail to create the output file!" << endl;
		exit(1);
	}
	else
	{
		unordered_map<char, node> map_char2node;
		priority_queue<node,vector<node>,greater<node>> frequency_queue;
		
		/*****开始读取文件到缓冲区*****/
		string buffer;
		ostringstream  tmp;
		tmp << infile.rdbuf();
		string  str = tmp.str();
		cout << "The file has been read in." << endl;
		/*****开始读取文件完毕*****/


		/*****开始统计频率******/
		node table[256];
		Count_frequency(table, map_char2node, str);
		cout << "The frequency of characters has been counted." << endl;
		for (unordered_map<char, node>::iterator its = map_char2node.begin(); its != map_char2node.end(); its++)
		{
			frequency_queue.push(its->second);
		}
		/*****统计频率完毕******/


		/****开始建立树****/
		node* root = BuildTree(map_char2node,frequency_queue); //生成哈夫曼树
		unordered_map<char, string> map_char2str;
		GenerateHuffmanCoding(map_char2node, map_char2str, root);  //生成每个字节对应编码
		cout << "The Huffman tree has been established." << endl;
		/*****哈夫曼树建立完毕****/

		/******开始压缩*****/
		ofstream outfile;
		outfile.open(output_name, ios::binary);  //打开目标文件
		if (outfile.is_open() == 0)
		{
			cout << "fail to create new file!" << endl;
			exit(1);
		}
		PreOrderReserveTree(outfile, root);//把建立好的哈夫曼树存入目标文件
		cout << "The Huffman tree has been restored in object file." << endl;
		Compression(outfile, map_char2str, str);
		/*****压缩完毕*****/

		PostOrderDeleteTree(root); //销毁哈夫曼树
		root = NULL;
		outfile.close(); //关闭目标文件
		infile.close();   //关闭输入文件
		cout << "zipped!" << endl;
	}
}

//解压选项对应的函数
void Unzip_file(ifstream& infile, const char* output_name)
{
	ofstream outfile;
	outfile.open(output_name, ios::binary);
	if (outfile.is_open() == 0)
	{
		cerr << "fail to create the output file!" << endl;
		return;
	}
	else
	{
		node* root = NULL;
		//将存放在文件开头的Huffman树读进来
		PreOrderReadTree(infile, root);
		cout << "The Huffman tree has been read in." << endl;

		node* track = root;
		if (!track)
			return;
		while (infile.peek() != EOF)
		{
			unsigned int len = 0;
			infile.read((char*)&len, sizeof(short int)); //获取之后的一个block信息
			bitset<BLOCK_SIZE>block;
			infile.read((char*)&block, sizeof(block));
			string code = block.to_string().c_str();
			char ch='0';
			unsigned int i = BLOCK_SIZE - len;
			for (; i < BLOCK_SIZE; i++)
			{
				ch = code[i];
				if (ch == '0')
					track = track->lchild;
				else
					track = track->rchild;
				if(track->tag==0)   //到这里说明是叶结点！
				{
					char ch2 = track->data;
					outfile.write(&ch2, sizeof(char));
					track = root;
				}
			}
		}
		PostOrderDeleteTree(root);
		root = NULL;
	}
	infile.close();
	outfile.close();
	cout << "unzipped!" << endl;
}
