/*************************************
*Author: Kaixu Chen   Moondok
*Date: 2022-05-16 10:59:22
*LastEditTime: 2022-05-30 11:10:46
*Description:
 ***************************************/
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<fstream>

void Initialize(std::vector<int>& unsortedList);
void BuildHeap(std::vector<int>& unsortedList, const unsigned int k);
void AdjustHeap(std::vector<int>& unsortedList, const unsigned int k,int i)
{
    int end = (k / 2) - 1;  //这是最后父节点的下标
    //int i = 0;//起点
    while (i <= end)  //当前结点不是叶子
    {
        if ((i + 1) * 2 < k)
        {
            if (unsortedList.at(i) >= unsortedList.at((i + 1) * 2 - 1) && unsortedList.at(i) >= unsortedList.at((i + 1) * 2))
                break;
            else
            {
                int pos = unsortedList.at((i + 1) * 2 - 1) >= unsortedList.at((i + 1) * 2) ? (i + 1) * 2 - 1 : (i + 1) * 2;
                int tem = unsortedList.at(i);
                unsortedList.at(i) = unsortedList.at(pos);
                unsortedList.at(pos) = tem;;
                i = pos;
                //std::cout<<pos<<std::endl;
            }
        }
        else //说明是只有一个左结点的情况，到了末尾
        {
            if (unsortedList.at(i) >= unsortedList.at((i + 1) * 2 - 1))
            {
                break;
            }
            else
            {
                int pos =(i + 1) * 2 - 1;
                int tem = unsortedList.at(i);
                unsortedList.at(i) = unsortedList.at(pos);
                unsortedList.at(pos) = tem;
                i = pos;
                // std::cout<<pos<<std::endl;
            }

        }

    }

}
int Find_Target(std::vector<int>& unsortedList, unsigned int k);
int main()
{
    srand((unsigned int)time(NULL));
    //std::fstream os("heapselect.txt",std::ios::out);
    for (int i = 10000; i < 10001; i += 100)
    {
        std::vector<int> unsortedList(i);
        Initialize(unsortedList);
        for (int i = 0; i < 10; i++)
            std::cout << unsortedList.at(i)<<" ";
        std::cout<< std::endl;
        unsigned int k = rand() % (unsortedList.size());
        //k = 8;
        std::cout << "k:" << k << std::endl;
        //clock_t start = clock();
        std::cout << i << " The k-th minimum of the array is " << Find_Target(unsortedList, k) << std::endl;
        //clock_t end = clock();
        //std::cout << (double)(end - start) / CLOCKS_PER_SEC << "\n";
    //std::vector<int> unsortedList(3000);
    //Initialize(unsortedList);
        std::sort(unsortedList.begin(), unsortedList.end());
        std::cout << unsortedList.at(k - 1);
        //std::cin>>k;
    }

    return 0;
}

void Initialize(std::vector<int>& unsortedList)
{

    for (unsigned i = 0; i < unsortedList.size(); i++)
        unsortedList.at(i) = rand() % 20001;
}

int Find_Target(std::vector<int>& unsortedList, unsigned int k)
{
    k = std::min(static_cast<unsigned int>(unsortedList.size()), k);
    //此时前k个元素就是一个堆，首先建立这个最大堆
    BuildHeap(unsortedList, k);
    for (unsigned int i = k; i < unsortedList.size(); i++)
    {
        if (unsortedList.at(i) < unsortedList.at(0)) //如果后面的元素小于堆顶，更换当前堆顶，并重新搭建最大堆
        {
            int tem = unsortedList.at(i);
            unsortedList.at(i) = unsortedList.at(0);
            unsortedList.at(0) = tem;
            //BuildHeap(unsortedList,k);
            AdjustHeap(unsortedList, k,0);
        }
    }
    return unsortedList.at(0);

}

void BuildHeap(std::vector<int>& unsortedList, const unsigned int k)
{
    int end = (k / 2) - 1;  //这是第一个父节点的下标
    for (int i = end; i >= 0; i--)
    {
        AdjustHeap(unsortedList, k, i);
        /**
        int lchild = (i + 1) * 2 - 1;//左孩子下标

        int pos;//需要和父节点比较的孩子结点坐标
        if (lchild == k - 1)//假如没有右孩子
            pos = lchild;
        else
            pos = unsortedList.at(lchild) > unsortedList.at(lchild + 1) ? lchild : lchild + 1;
        if (unsortedList.at(pos) > unsortedList.at(i))
        {
            int tem = unsortedList.at(pos);
            unsortedList.at(pos) = unsortedList.at(i);
            unsortedList.at(i) = tem;
        }
        */
    }
}