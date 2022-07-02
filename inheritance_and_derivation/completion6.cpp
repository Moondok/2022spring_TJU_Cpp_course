/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-15 15:17:51
*LastEditTime: 2022-06-15 16:15:45
*Description: 
 ***************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<iostream>
class Teacher
{
public:
    void set(const int n,const char * newname,const char s);
    void display();

private:
    int num=0;
    char name[20]={'\0'};
    char sex='\0';
};
void Teacher::set(const int n,const char * newname,const char s)
{
    num=n;
    int len=static_cast<int>(strlen(newname));
    strcpy(name,newname);
    name[len]='\0';
    sex=s;
}
void Teacher::display()
{
    std::cout<<"姓名: "<<name<<" 教工号: "<<num<<" 性别: "<<sex;
}


class BirthDate
{
public:
    void set(const int y,const int m,const int d)
    {
        year=y;
        month=m;
        day=d;
    }
    void display()
    {
        std::cout<<" 生日: "<<year<<"-"<<month<<"-"<<day<<std::endl;
    }
private:
    int year=0;
    int month=0;
    int day=0;

};

class Professor : public Teacher
{
public:
    Professor()
    {};
    Professor(const int n,const char * newname,const char s,const int y,const int m,const int d)
    {
        Teacher::set(n,newname,s);
        birthday.set(y,m,d);
    }
    void display()
    {
        Teacher::display();
        birthday.display();
    }
    BirthDate & get_Birthday()
    {
        return birthday;
    }
private:
    BirthDate birthday;
};

void fun1(Teacher &t)
{
    t.set(10000,"张三",'m');
}

void fun2(BirthDate &b)
{
    std::cout<<"输入改变的日期:";
    int y,m,d;
    std::cin>>y>>m>>d;
    b.set(y,m,d);
}

int main()
{
    Professor professor(0,"佚名",'m',0,0,0);
    fun1(professor);
    fun2(professor.get_Birthday());
    professor.display();
}