/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-12 19:02:26
*LastEditTime: 2022-06-15 08:48:01
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

class Student1 : public Student
{

public:

    Student1()
    {
        addr=new(nothrow)char[30];
        if(addr==NULL)
        {
            cerr<<"fail to allocate memeory!"<<endl;
            exit(EXIT_FAILURE);
        }   
    }
    void get_value_1()
    {
        cin >> age >> addr;
    }

    void display_1()
    {
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
    stud.get_value();
    stud.get_value_1();
    stud.display();
    stud.display_1();
    return 0;
}