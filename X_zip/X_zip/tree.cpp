#include<iostream>
#include"X_zip.h"
using namespace std;

/***********************************************************************
功能:根据字符和结点的对应关系 以及 根据字符频率对结点进行排序的优先队列建立哈夫曼树
参数:map_char2node:实现字符到结点的一一对应的unordered_map对象引用
	 frequency_queue:根据字符频率对结点排序的优先队列
返回值:哈夫曼树根节点
****************************************************************************/
node* BuildTree(unordered_map<char, node>& map_char2node, priority_queue<node, vector<node>, greater<node>>& frequency_queue)
{
	//开始建立树
	node* root = NULL; //huffman树根结点
	while (true)
	{
		node* leftnode = new(nothrow) node;
		if (leftnode == NULL)
		{
			cout << "Something wrong happened!" << endl;
			exit(1);
		}
		leftnode->data = frequency_queue.top().data;
		leftnode->fre = frequency_queue.top().fre;
		leftnode->lchild = frequency_queue.top().lchild;
		leftnode->rchild = frequency_queue.top().rchild;
		leftnode->tag = frequency_queue.top().tag;
		frequency_queue.pop();
		if (leftnode->tag != 0)  //newnode1不是叶结点
		{
			if (leftnode->lchild)
			{
				leftnode->lchild->parent = leftnode;
				if (leftnode->lchild->tag == 0)
					map_char2node[leftnode->lchild->data] = *leftnode->lchild;
			}
			if (leftnode->rchild)
			{
				leftnode->rchild->parent = leftnode;
				if (leftnode->rchild->tag == 0)
					map_char2node[leftnode->rchild->data] = *leftnode->rchild;
			}
		}
		if (frequency_queue.empty() == true)
		{
			root = leftnode;  //说明找到根结点啦
			break;
		}
		node* rightnode = new (nothrow) node;
		if (rightnode == NULL)
		{
			cout << "Something wrong happened!" << endl;
			exit(1);
		}
		rightnode->data = frequency_queue.top().data;
		rightnode->fre = frequency_queue.top().fre;
		rightnode->lchild = frequency_queue.top().lchild;
		rightnode->rchild = frequency_queue.top().rchild;

		rightnode->tag = frequency_queue.top().tag;
		frequency_queue.pop();
		if (rightnode->tag != 0)  //newnode1不是叶结点
		{
			if (rightnode->lchild)
			{
				rightnode->lchild->parent = rightnode;
				if (rightnode->lchild->tag == 0)
					map_char2node[rightnode->lchild->data] = *rightnode->lchild;
			}
			if (rightnode->rchild)
			{
				rightnode->rchild->parent = rightnode;
				if (rightnode->rchild->tag == 0)
					map_char2node[rightnode->rchild->data] = *rightnode->rchild;
			}
		}
		leftnode->position = 0;
		rightnode->position = 1;
		node* merged_node = new node; //这里的地址不等同于pop出来的东西的地址！！！
		merged_node->fre = leftnode->fre + rightnode->fre;
		merged_node->lchild = leftnode;
		merged_node->rchild = rightnode;
		frequency_queue.push(*merged_node);
		delete merged_node; //即用即删除
	}
	return root;
}

/*************************************
* 功能:通过后序遍历的递归方法销毁一棵二叉树
* 参数:二叉树根结点
* ***********************************/
void PostOrderDeleteTree(node* root) //递归销毁树
{
	if (root == NULL)
		return;
	PostOrderDeleteTree(root->lchild);
	PostOrderDeleteTree(root->rchild);
	delete root;
}


/******************************************
功能:压缩文件时通过先序遍历将哈夫曼树存入目标文件中
参数: outfile: 文件输出流对象
      root:待存的哈夫曼树根结点
*******************************************/
void PreOrderReserveTree(ofstream& outfile, node* root)
{
	outfile.write((char*)&root->tag, sizeof(bool));
	if (root->tag == 0)
		outfile.write(&root->data, sizeof(char));
	else
	{
		char ch_nofind = '#';
		char ch_find = '*';
		if (!root->lchild)
			outfile.write(&ch_nofind, sizeof(char));
		else
			outfile.write(&ch_find, sizeof(char));
		if (!root->rchild)
			outfile.write(&ch_nofind, sizeof(char));
		else
			outfile.write(&ch_find, sizeof(char));

		if (root->lchild)
			PreOrderReserveTree(outfile, root->lchild);
		if (root->rchild)
			PreOrderReserveTree(outfile, root->rchild);
	}
}

/******************************************
功能:解压文件时通过先序遍历将哈夫曼树读入程序中
参数: outfile: 文件输入流对象
	  root:待存的哈夫曼树根结点的引用
*******************************************/
void PreOrderReadTree(ifstream& infile, node*& root)
{
	bool tag;
	infile.read((char*)&tag, sizeof(bool));
	root = new(nothrow) node;
	if (root == NULL)
	{
		cerr << "Something wrong happened!" << endl;
		exit(1);
	}
	root->tag = tag;
	if (tag == 0)
	{
		char content;
		infile.read(&content, sizeof(char));
		root->data = content;
		return;
	}
	else
	{
		char lefttag, righttag;
		infile.read(&lefttag, sizeof(char));
		infile.read(&righttag, sizeof(char));
		if (lefttag == '*')
			PreOrderReadTree(infile, root->lchild);
		if (righttag == '*')
			PreOrderReadTree(infile, root->rchild);
	}
}


