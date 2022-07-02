#include<iostream>
using namespace std;

class dateToDay
{
public:
    dateToDay(int, int, int);    // 通过传参构建
    // dateToDay();              // 构建时从键盘读入 实现方式二选一
    void setDate(int, int, int); // 设置日期
    // void setDate();           // 从键盘读入设置日期 实现方式二选一
    // 合法性检查应该在构建/设置时完成
    void display();              // 将计算结果输出(即本年内第几天)
private:
    bool checkLeap();            // 该函数用于检查闰年
    bool checkValid();           // 该函数用于检查合法
    int computeDay();            // 该函数用于计算日期
    int year;
    int month;
    int day;
};

int main()
{
    cout<<"请输入一个日期:";
    int year,month,day;
    cin>>year>>month>>day;
    if(!cin.good()||cin.peek()=='.')  //防止小数点
    {
        cout<<"数据非法，程序退出!"<<endl;    
        return 0;
    }
    dateToDay calculator1(year,month,day);
    calculator1.display();

    cout<<"请输入一个日期:";
    cin>>year>>month>>day;
    if(!cin.good()||cin.peek()=='.')//防止小数点
    {
        cout<<"数据非法，程序退出!"<<endl;    
        return 0;
    }
    calculator1.setDate(year,month,day);
    calculator1.display();
    return 0;
    
}

bool dateToDay::checkLeap()
{
    return (year%400==0||(year%100!=0&&year%4==0))?1:0;
}

int dateToDay::computeDay()
{
    int table[12]={31,28,31,30,31,30,
                   31,31,30,31,30,31};
    table[1]+=checkLeap();
    int num=0;
    for(int i=1;i<month;i++)
        num+=table[i-1];
    num+=day;
    return num;
}

bool dateToDay::checkValid()
{
    bool re=1;
    if(year<1||year>9999)
        re=0;
    else if(month<1||month>12)
        re=0;
    else
    {
        int table[12]={31,28,31,30,31,30,
                       31,31,30,31,30,31};
        table[1]+=checkLeap();
        if(day<1||day>table[month-1])
            re=0;
    }
    return re;
}

dateToDay::dateToDay(int y,int m,int d)
{
    year=y;
    month=m;
    day=d;
    if(!checkValid())
    {
        cout<<"数据非法，程序退出"<<endl;
        exit(0);
    }
}

void dateToDay::display()
{
    cout<<month<<"月"<<day<<"日是"<<year<<"年的第"<<computeDay()<<"天"<<endl; 
}

void dateToDay::setDate(int y,int m,int d)
{
    year=y;
    month=m;
    day=d;
    if(!checkValid())
    {
        cout<<"数据非法，程序退出"<<endl;
        exit(0);
    }
}

