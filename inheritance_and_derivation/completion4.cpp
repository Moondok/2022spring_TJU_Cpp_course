/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-15 13:32:39
*LastEditTime: 2022-06-15 13:59:15
*Description: 
 ***************************************/
#include <iostream>

using namespace std;

class Student
{
public:
    Student()
    {
        name=new(nothrow)char[20];
        if(name==NULL)
        {
            cerr<<"fail to allocate memeory!"<<endl;
            exit(EXIT_FAILURE);
        }   
    }
    ~Student()
    {
        if(name)
            delete[] name;
    }

protected:
    int num=0;
    char* name=NULL;
    char sex='\0';
};

class Student1 : public Student
{
public:
    Student1()
    {
        addr=new(nothrow)char[20];
        if(addr==NULL)
        {
            cerr<<"Fail to allocate memory!"<<endl;
            exit(EXIT_FAILURE);
        }
    }
    void get_value1();
    void display1();
    ~Student1()
    {
        if(addr)
            delete[] addr;
    }
private:
    int age=0;
    char* addr=NULL;
};

void Student1::get_value1()
{
    cin >> num >> name >> sex;
    cin >> age >> addr;
}

void Student1::display1()
{
    cout << " name: " << name << endl;
    cout << " num: " << num << endl;
    cout << " sex: " << sex << endl;
    cout << " age: " << age << endl;
    cout << " address: " << addr << endl;
}

int main()
{
    Student1 stud1;
    stud1.get_value1();
    stud1.display1();
    return 0;
}
/*****结果*****
 name: 输入的第二个字段
 num: 输入的第一个字段
 sex: 输入的第3个字段
 age: 输入的第四个字段
 address: 输入的第五个字段
*********/

/*******分析******
 * 首先创建了一个Student1 对象 Stud1,
 * 该类由Student 类继承而来，继承方式为公有继承，
 * 因此，父类中protected的 name,num和sex在子类中也是protected的
 * 因此子类中的display1函数和get_value1函数可以直接操作父类中的成员
 * 在主函数中，程序通过Stud1的get_value1函数输入了属于父类的3个成员和
 * 属于子类的2个成员并通过display1函数输出
 * *****************/

/****公有继承和保护继承的区别*****
 * 在公有继承下，父类中公有的成员在子类中仍为公有，外界可以直接访问，
 * 在保护继承下，父类中公有成员在子类中为保护，外界不可以直接访问
 * 因此，在外界需要直接访问子类从父类中继承的公有成员时，保护继承不能替代公有继承**/