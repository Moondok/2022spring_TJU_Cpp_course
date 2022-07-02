/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-15 13:06:32
*LastEditTime: 2022-06-15 13:29:57
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

class Student1 : protected Student
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
    void get_value1()
    {
        cin >> num >> name >> sex;
        cin >> age >> addr;
    }
    void display1()
    {
        cout << " num: " << num << endl;
        cout << " name: " << name << endl;
        cout << " sex: " << sex << endl;
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
    Student1 stud1;
    stud1.get_value1();
    stud1.display1();
    return 0;
}