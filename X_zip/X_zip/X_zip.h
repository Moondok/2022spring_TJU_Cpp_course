#pragma once
#include<fstream>
#include<unordered_map>
#include<queue>
#include<vector>
#include<bitset>
using namespace std;
#define BLOCK_SIZE 4096  //将4096个编码字节压缩成一个整体，不足补0
struct node
{
	bool position = 0;  //用来判断当前结点是其父节点的左孩子还是右孩子，默认左孩子
	bool tag = 1;    //用来判断是否为叶结点，默认不是
	char data = '\0';  //字节数据
	long long int fre = 0;  //出现频率
	node* lchild = NULL;  //左孩子
	node* rchild = NULL;   //右孩子
	node* parent = NULL;  //父节点
	bool operator >(const node& a)const //重载运算符
	{
		return this->fre> a.fre;
	}
};

//压缩文件
void Zip_file(ifstream& infile, const char* output_name);

//解压文件
void Unzip_file(ifstream& infile, const char* output_name);

//通过后序遍历的递归方法销毁一棵二叉树
void PostOrderDeleteTree(node* root);

//压缩文件时通过先序遍历将哈夫曼树存入目标文件中
void PreOrderReserveTree(ofstream& outfile, node* root);

//解压文件时通过先序遍历将哈夫曼树读入程序中
void PreOrderReadTree(ifstream& infile, node*& root);

//根据字符和结点的对应关系 以及 根据字符频率对结点进行排序的优先队列建立哈夫曼树
node* BuildTree(unordered_map<char, node>& map_char2node, priority_queue<node, vector<node>, greater<node>>& frequency_queue);

//统计文件中各字节的出现频率
void Count_frequency(node* table, unordered_map<char, node>& map_char2node, string& str);

//通过待压缩文件中的每个字节对应的哈夫曼编码压缩文件
void Compression(ofstream& outfile, unordered_map<char, string>& map_char2str, string& str);

//根据已建成的哈夫曼树生成每个字节对应的编码
void GenerateHuffmanCoding(unordered_map<char, node>& map_char2node, unordered_map<char, string>& map_char2str, node* root);