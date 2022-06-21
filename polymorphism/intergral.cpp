/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-21 20:33:12
*LastEditTime: 2022-06-21 21:19:45
*Description: 
 ***************************************/
#include <iostream>
#include <cmath>

using namespace std;

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
class integral
{
protected:
    double lower=0;
    double upper=0;
    friend istream& operator>> (istream& o,integral & obj);
public:
    virtual double value()const=0;
};

istream& operator>> (istream& i,integral & obj)
{
    i>>obj.lower>>obj.upper;
    return i;
}

class integral_sin:public integral
{
public:
    virtual double value()const
    {
        double sum=0;
        double delta_x=(upper-lower)/10000;
        for(int i=0;i<=10000;i++)
            sum+=sin(lower+i*delta_x)*delta_x;
        return sum;
    }
};

class integral_cos:public integral
{
public:
    virtual double value()const
    {
        double sum=0;
        double delta_x=(upper-lower)/10000;
        for(int i=0;i<=10000;i++)
            sum+=cos(lower+i*delta_x)*delta_x;
        return sum;
    }
};

class integral_exp:public integral
{
public:
    virtual double value()const
    {
        double sum=0;
        double delta_x=(upper-lower)/10000;
        for(int i=0;i<=10000;i++)
            sum+=exp(lower+i*delta_x)*delta_x;
        return sum;
    }
};
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main()
{
    integral_sin s1;
    integral_cos s2;
    integral_exp s3;
    integral *p;

    cout << "请输入上下限：";
    cin >> s1;
    p = &s1;
    cout << "∫sinxdx的计算结果为：" << (p->value()) << endl;

    cout << "请输入上下限：";
    cin >> s2;
    p = &s2;
    cout << "∫cosxdx的计算结果为：" << (p->value()) << endl;

    cout << "请输入上下限：";
    cin >> s3;
    p = &s3;
    cout << "∫expxdx的计算结果为：" << (p->value()) << endl;

    return 0;
}
