/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-15 14:01:44
*LastEditTime: 2022-06-15 15:09:57
*Description: 
 ***************************************/
#include<iostream>

class Teacher
{
private:
    char name[20]={'\0'};
    int age=0;
    char sex='\0';
    char addr[20]={'\0'};
    unsigned long long int phone_num=0;
    char title[20]={'\0'};
public:
    void get_value();
    void display();
};
void Teacher::get_value()
{
    std::cin>>name>>age>>sex>>addr>>phone_num>>title;
}
void Teacher::display()
{
    std::cout<<"姓名: "<<name<<std::endl;
    std::cout<<"年龄: "<<age<<std::endl;
    std::cout<<"性别: "<<sex<<std::endl;
    std::cout<<"地址: "<<addr<<std::endl;
    std::cout<<"电话: "<<phone_num<<std::endl;
    std::cout<<"职称: "<<title<<std::endl;
}

class Cadre
{
protected:
    char name[20]={'\0'};
    int age=0;
    char sex='\0';
    char addr[20]={'\0'};
    unsigned long long int phone_num=0;
    char post[20]={'\0'};
public:
    void get_value();
    void display();
};
void Cadre::get_value()
{
    std::cin>>name>>age>>sex>>addr>>phone_num>>post;
}
void Cadre::display()
{
    std::cout<<"姓名: "<<name<<std::endl;
    std::cout<<"年龄: "<<age<<std::endl;
    std::cout<<"性别: "<<sex<<std::endl;
    std::cout<<"地址: "<<addr<<std::endl;
    std::cout<<"电话: "<<phone_num<<std::endl;
    std::cout<<"职务: "<<post<<std::endl;
}

class Teacher_Cadre: protected Teacher,protected Cadre
{
private: 
    int wages=0;
public:
    void show();
    void get_value();
};

void Teacher_Cadre::show()
{
    Teacher::display();
    std::cout<<"职务: "<<post<<std::endl;
    std::cout<<"薪水: "<<wages<<std::endl;
}

void Teacher_Cadre::get_value()
{
    Teacher::get_value();
    std::cin>>post>>wages;
}

int main()
{
    int option=0;
    std::cin>>option;
    switch(option)
    {
        case 0:
        {
            Teacher teacher;
            teacher.get_value();
            teacher.display();
            break;
        }
        case 1:
        {
            Cadre cadre;
            cadre.get_value();
            cadre.display();
            break;
        }
        case 2:
        {
            Teacher_Cadre obj;
            obj.get_value();
            obj.show();
            break;
        }
        default:
            break;
    }
    return 0;
}


