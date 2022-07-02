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

int main()
{
    Student stud(101, 78.5); //调用构造函数，，初始化num=101,score=78.5
    stud.display();  //打印num和score的值 
    stud.change(101, 80.5);  //调用公有成员函数change,将num的值修改（实际没变）为101，score修改为80.5
    stud.display();  //打印num和score的值
    return 0;
}

/*************运行结果**********
 101 78.5
 101 80.5
 * ******************************/