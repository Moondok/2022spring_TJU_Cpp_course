#include <iostream>

using namespace std;

class Date
{
public:
    Date(int, int, int);
    Date(int, int);
    Date(int);
    Date();
    void display();

private:
    int month;
    int day;
    int year;
};

//三个参数的构造函数，在初始化表列中实现为全部3个私有成员赋初值的操作
Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}

//2个参数的构造函数，在初始化表列中实现为month和day2个私有成员赋初值的操作，year的赋值在函数体内完成
Date::Date(int m, int d) : month(m), day(d)
{
    year = 2005;
}

//1个参数的构造函数，在初始化表列中实现为month私有成员赋初值的操作，day和year的赋值在函数体内完成
Date::Date(int m) : month(m)
{
    day = 1;
    year = 2005;
}

//无参数的构造函数，在函数体内为3个私有成员赋默认值，year=2005,month=1,day=1
Date::Date()
{
    month = 1;
    day = 1;
    year = 2005;
}

void Date::display()
{
    cout << month << "/" << day << "/" << year << endl;
}

int main()
{
    Date d1(10, 13, 2005);  //调用三个参数的构造函数，month=10,day=13,year=2005
    Date d2(12, 30);     //调用2个参数的构造函数，month=12,day=30,year的值在函数体内默认给出，为2005
    Date d3(10);   //调用1个参数的构造函数，month=1,day和year的值在函数体内默认给出，day=1,year=2005
    Date d4;    //调用无参的构造函数，在该构造函数体内为三个私有成员赋值，day=1,month=1,year=2005

    d1.display();
    d2.display();
    d3.display();
    d4.display();

    return 0;
}

/************预期结果*******************
10/13/2005
12/30/2005
10/1/2005
1/1/2005
***************************************/


