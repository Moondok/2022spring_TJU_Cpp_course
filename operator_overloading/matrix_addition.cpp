/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-05-27 16:34:09
*LastEditTime: 2022-06-03 20:27:32
*Description: 
 ***************************************/
#include<iostream>
#include<iomanip>
#include<stdlib.h>
const unsigned int nrows=2;
const unsigned int ncols=3;
class Array;
Array operator +(const Array & a,const Array&b);

class Array
{
private:
    unsigned int row=0;
    unsigned int col=0;
    friend Array operator +(const Array & a,const Array&b);
    int content[nrows][ncols];
public:
    Array& operator=(const Array & a)
    {
        for(unsigned int i=0;i<nrows;i++)
            for(unsigned int j=0;j<ncols;j++)
                this->content[i][j]=a.content[i][j]; //同一个类的不同对象互为友元
        return *this;
    }

    Array():row(nrows),col(ncols)
    {
        for(unsigned int i=0;i<row;i++)
            for(unsigned int j=0;j<col;j++)
                content[i][j]=0;
    }
    
    void display()const
    {
        for(unsigned int i=0;i<nrows;i++)
        {
            for(unsigned int j=0;j<ncols;j++)
                std::cout<<std::setiosflags(std::ios::left)<<std::setw(7)<<content[i][j];
            std::cout<<std::endl;
        }
            
    }
    void readFromKeyboard()
    {
        for(unsigned int i=0;i<nrows;i++)
            for(unsigned int j=0;j<ncols;j++)
                std::cin>>content[i][j];

    }
    unsigned int getRows() const
    {
        return row;
    }
     unsigned int getCols() const
    {
        return col;
    }
    
};

Array operator +(const Array & a,const Array&b)
{
    Array tmp;
    for(unsigned int i=0;i<a.getRows();i++)
        for(unsigned int j=0;j<a.getCols();j++)
            tmp.content[i][j]=a.content[i][j]+b.content[i][j];

    return tmp;
}

int main()
{
    Array a, b, c;        // 固定 2 行 3 列
    std::cout<<"input matrix a:"<<std::endl;
    a.readFromKeyboard(); // 从键盘读取矩阵 a 的数据
    std::cout<<"matrix a :"<<std::endl;
    a.display();

    std::cout<<"input matrix b:"<<std::endl;
    b.readFromKeyboard(); // 从键盘读取矩阵 b 的数据
    std::cout<<"matrix b :"<<std::endl;
    b.display();

    std::cout<<"output matrix c=a+b:"<<std::endl;
    c = a + b;
    c.display();
    return 0;
}