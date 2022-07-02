#include <iostream>

using namespace std;

class Student
{
public:
    Student(int n, float s):num(n),score(s){}  //带两个参数的构造函数
    void change(int n, float s) { num = n; score = s; }  //修改私有成员
    void display() { cout << num << " " << score << endl; }  //打印两个私有成员
private:
    int num;
    float score;
};

void fun(Student& student,int new_num,float new_score)
{
    student.change(new_num,new_score);
    student.display();
}

int main()
{
    Student stud(101, 78.5); //调用构造函数，，初始化num=101,score=78.5
    stud.display();  //打印num和score的值 
    
    fun(stud,101,80.5);
    return 0;
}