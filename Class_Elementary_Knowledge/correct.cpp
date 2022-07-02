#include <iostream>

using namespace std;

class Date
{
public:
    Date(int = 1, int = 1, int = 2005);
   // Date(int, int); //该2个参数的构造函数和第8行有3个默认值的构造函数，在用户采用带2个参数的构造时会有冲突，编译器不知道该调用哪个函数，因此会编译错误
   // Date(int); //该1个参数的构造函数和第8行有3个默认值的构造函数，在用户采用带1个参数的构造时会有冲突，编译器不知道该调用哪个函数，因此会编译错误
   // Date();  //该无参构造函数和第8行有默认值的构造函数，在用户采用无参构造时会有冲突，编译器不知道该调用哪个函数，因此会编译错误
    void display();
private:
    int month;
    int day;
    int year;
};
Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}

/*注释掉以下3个和第8行有冲突的3个构造函数
Date::Date(int m, int d) : month(m), day(d)
{
    year = 2005;
}
Date::Date(int m) : month(m)
{
    day = 1;
    year = 2005;
}

Date::Date()
{
    month = 1;
    day = 1;
    year = 2005;
}
*/
void Date::display()
{
    cout << month << "/" << day << "/" << year << endl;
}
int main()
{
    Date d1(10, 13, 2005);
    Date d2(12, 30);
    Date d3(10);
    Date d4;
    d1.display();
    d2.display();
    d3.display();
    d4.display();
    return 0;
}