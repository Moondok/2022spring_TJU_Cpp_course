/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-15 09:07:10
*LastEditTime: 2022-06-15 13:03:50
*Description: 
 ***************************************/
#include<iostream>
#include<stdlib.h>
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
    void get_value()
    {
        cin >> num >> name >> sex;
    }

    void display()
    {
        cout << " name: " << name << endl;
        cout << " num: " << num << endl;
        cout << " sex: " << sex << endl;
    }

    ~Student()
    {
        if(name)
            delete[] name;
    }

private:
    int num=0;
    char* name=NULL;
    char sex='\0';
};

class Student1 : private Student
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
    void get_value_1()
    {
        get_value();
        cin >> age >> addr;
    }

    void display_1()
    {
        display();
        cout << " age: " << age << endl;
        cout << " address: " << addr << endl;
    }

    ~Student1()
    {
        if(addr)
            delete[] addr;
    }
private:
    int age=0;
    char* addr=NULL;
};

int main()
{
    Student1 stud;
    stud.get_value_1();
    stud.display_1();
    return 0;
}