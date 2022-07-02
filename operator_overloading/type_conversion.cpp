/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-05-27 19:26:45
*LastEditTime: 2022-06-03 19:27:29
*Description: 
 ***************************************/


/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/

class Teacher
{
private:
    int id=0;
    int age=0;
    int gender=0;
    char name[16]={};
public:
    Teacher()
    {}
    Teacher(int a,int b,int c, const char * str):id(a),age(b),gender(c)
    {
        strcpy(name,str);
    }
    void show_info()
    {
        cout<<"the id of this teacher is "<<id<<endl;
        cout<<"the age of this teacher is "<<age<<endl;
        cout<<"the gender of this teacher is "<<(gender?"male":"female")<<endl;
        cout<<"the name of this teacher is "<<name<<endl;
    }
};

class Student
{
private:
    private:
    int id=0;
    int age=0;
    int gender=0;
    char name[16]={};
public:
    Student()
    {}
    Student(int a,int b,int c, const char * str):id(a),age(b),gender(c)
    {
        strcpy(name,str);
    }
    void show_info()
    {
        cout<<"the id of this student is "<<id<<endl;
        cout<<"the age of this student is "<<age<<endl;
        cout<<"the gender of this student is "<<(gender?"male":"female")<<endl;
        cout<<"the name of this student is "<<name<<endl;
    }
    explicit operator Teacher() const
    {
        Teacher tmp(this->id,this->age,this->gender,this->name);
        return tmp;
    }
};

/**********************************************
*
*    TO-DO END
*
***********************************************/
