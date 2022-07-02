#include<iostream>

using namespace std;

class student
{
private:
    int num;
    int score;
public:
    student(int n,int s):num(n),score(s)
    { };
    student():num(0),score(0)
    { };

    void print_info()
    {
        cout<<"该生的学号是 "<<this->num<<" ,成绩是"<<this->score<<endl;
    }
};

int main()
{

    student students[5];
    student* p=students;
    int num,score;
    for(int i=0;i<5;i++)
    {
        cout<<"请输入第"<<i+1<<"个学生的学号和成绩:";
        cin>>num>>score;
        *p=student(num,score);
        p++;
    }

    p=students;
    for(;p-students<5;p++)
        if((p-students)%2==0)
            p->student::print_info();

    p=NULL;
    return 0;
}