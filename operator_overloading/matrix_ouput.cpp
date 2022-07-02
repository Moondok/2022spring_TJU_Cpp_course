/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-05-27 17:23:44
*LastEditTime: 2022-06-03 20:32:25
*Description: 
 ***************************************/
#include<iostream>
#include<iomanip>
#include<stdlib.h>
const unsigned int nrows=2;
const unsigned int ncols=3;
class Array;
std::istream & operator>>(std::istream &i,Array & a);
std::ostream & operator<<(std::ostream &o,Array & a);

class Array
{
private:
    friend std::istream & operator>>(std::istream &i,Array & a);
    friend std::ostream & operator<<(std::ostream &i,Array & a);
    unsigned int row=0;
    unsigned int col=0;
    int content[nrows][ncols];
public:
    Array operator +(const Array & a)const
    {
        Array tmp;
        for(unsigned int i=0;i<a.getRows();i++)
            for(unsigned int j=0;j<a.getCols();j++)
                tmp.content[i][j]=a.content[i][j]+this->content[i][j];

        return tmp;
    }
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
    unsigned int getRows() const
    {
        return row;
    }
     unsigned int getCols() const
    {
        return col;
    }
    
};

//重载流提取
std::istream & operator>>(std::istream &i,Array & a)
{
    for(unsigned int k=0;k<a.row;k++)
        for(unsigned int j=0;j<a.col;j++)
            i>>a.content[k][j];

    return i;
}
//重载流插入
std::ostream & operator<<(std::ostream &o,Array & a)
{
    for(unsigned int i=0;i<a.row;i++)
    {
        for(unsigned int j=0;j<a.col;j++)
            o<<std::setiosflags(std::ios::left)<<std::setw(7)<<a.content[i][j];
        std::cout<<std::endl;
    }
    return o;
}


int main()
{
    Array a, b, c;        // 固定 2 行 3 列
    std::cout<<"input matrix a:"<<std::endl;
    std::cin>>a;
    std::cout<<"matrix a :"<<std::endl;
    std::cout<<a;

    

    std::cout<<"input matrix b:"<<std::endl;
    std::cin>>b;
    std::cout<<"matrix b :"<<std::endl;
    std::cout<<b;

    std::cout<<"output matrix c=a+b:"<<std::endl;
    c = a + b;
    std::cout<<c;
    return 0;
}
