/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-06-23 12:08:28
*LastEditTime: 2022-06-24 11:06:34
*Description: 
 ***************************************/

#define _CRT_SECURE_NO_WARNINGS
#define ibsn_size 18
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<cmath>
#include<conio.h>

using namespace std;

inline void wait_for_press()
{
    cout << endl << "按任意键继续..." << endl;
    _getch();
}

class Book_Sale
{
protected:
    friend istream& operator>>(istream & i, Book_Sale& a);
    char * isbn; // 指向书籍编号的指针
                 // 存放书籍编号的空间需动态申请
                 // 书籍编号由 5 段 13 位数字组成，如 978-7-121-15535-2
    int    sales_volume;   // 销售量
    double original_price; // 原始价格
    double real_price;     // 实售价格
    double discount;       // 折扣
    double gross_sales;    // 销售总额
    void Fill()
    {
        int r=0;
        bool tag=0;
        for(int i=0;i<15;i++)
        {
            if(i!=3&&i!=5&&i!=9)
            {
                r+=(isbn[i]-'0')*(1+tag*2);
                tag=1-tag;  //取反
            }
        }
        r=10-r%10;
        isbn[15]='-';
        isbn[16]=(r==10)?'0':r+'0';

        real_price=original_price*discount;
        gross_sales=real_price*sales_volume;
    }
public:
//默认无参构造

    Book_Sale():isbn(NULL),sales_volume(0),original_price(0),real_price(0),discount(0),gross_sales(0)
    {
        isbn=new(nothrow) char[ibsn_size];
        if(isbn==NULL)
        {
            cerr<<"Something get Wrong!"<<endl;
            exit(EXIT_FAILURE);
        }
        strcpy(isbn,"978-7-121-");
        isbn[ibsn_size-1]='\0';
    };
    
    Book_Sale(int id,int volumn,int pre_price,double d):sales_volume(volumn),original_price(pre_price),discount(d)
    {
        isbn=new(nothrow) char[ibsn_size];
        if(isbn==NULL)
        {
            cerr<<"Something get Wrong!"<<endl;
            exit(EXIT_FAILURE);
        }
        strcpy(isbn,"978-7-121-");
        isbn[ibsn_size-1]='\0';
        for(int i=0;i<5;i++)
        {
            char tmp=id%10+'0';
            id/=10;
            isbn[ibsn_size-4-i]=tmp;
        }
        Fill(); //补完后面几位
    }

    Book_Sale(const Book_Sale& a) //复制构造
    {
        isbn=new(nothrow) char[ibsn_size];
        if(isbn==NULL)
        {
            cerr<<"Something get Wrong!"<<endl;
            exit(EXIT_FAILURE);
        }
        strcpy(isbn,a.isbn);
        this->sales_volume=a.sales_volume;
        this->original_price=a.original_price;
        this->discount=a.discount;
        this->real_price=a.real_price;
        this->gross_sales=a.gross_sales;
    }

    Book_Sale& operator=(const Book_Sale& a)  //赋值，运算符重载
    {
        if(isbn)
            delete isbn;
        isbn=new(nothrow) char[ibsn_size];
        if(isbn==NULL)
        {
            cerr<<"Something get Wrong!"<<endl;
            exit(EXIT_FAILURE);
        }
        strcpy(isbn,a.isbn);
        this->sales_volume=a.sales_volume;
        this->original_price=a.original_price;
        this->discount=a.discount;
        this->real_price=a.real_price;
        this->gross_sales=a.gross_sales;

        return *this;
    }

    void display()
    {
        cout<<"该书的ISBN号为:"<<this->isbn<<"，";
        cout<<"销量为:"<<this->sales_volume<<"本，";
        cout<<"原价为:"<<this->original_price<<"元，";
        cout<<"折扣为:"<<this->discount;
        cout<<"，现价为:"<<this->real_price<<"元，";
        cout<<"总销售额为:"<<gross_sales<<"元";
    }

    
    
    ~Book_Sale()
    {
        if(isbn)
            delete isbn;
    }

    void set(int id,int volumn,int pre_price,double d=1)
    {
        if(id!=-1)
        {
            for(int i=0;i<5;i++)
            {
                char tmp=id%10+'0';
                id/=10;
                isbn[ibsn_size-4-i]=tmp;
            }
        }
        if(volumn!=-1)
            this->sales_volume=volumn;
        if(pre_price!=-1)
            this->original_price=pre_price;
        if(fabs(discount+1)>1e-6)
            this->discount=d;
        Fill();
    }

    Book_Sale& operator+=(const int extra_volumn)
    {
        this->sales_volume+=extra_volumn;
        this->gross_sales=this->sales_volume*this->real_price;
        return *this;
    }

    Book_Sale& operator-=(const int extra_volumn)
    {
        this->sales_volume-=extra_volumn;

        this->gross_sales=this->sales_volume*this->real_price;
        return *this;
    }
    
    bool operator>(const Book_Sale& a) const
    {
        return this->gross_sales>a.gross_sales;
    }

    bool operator<(const Book_Sale& a) const
    {
        return this->gross_sales<a.gross_sales;
    }

    bool operator>=(const Book_Sale& a) const
    {
        return !(*this<a);
    }

    bool operator<=(const Book_Sale& a) const
    {
        return !(*this>a);
    }

    bool operator==(const Book_Sale &a)const
    {
        if(fabs(this->gross_sales-a.gross_sales)<1e-6)
            return true;
        else
            return false;
    }

    bool operator!=(const Book_Sale &a)const
    {
        return !(*this==a);
    }
};

istream& operator>>(istream & i, Book_Sale &a)
{
    int id;
    i>>id;
    for(int j=0;j<5;j++)
    {
        char tmp=id%10+'0';
        id/=10;
        a.isbn[ibsn_size-4-j]=tmp;
    }
    i>>a.sales_volume>>a.original_price>>a.discount;
    a.Fill();
    return i;
}


class Book_Sale_Limit:public Book_Sale
{
private:
    int limit=0;
    friend istream& operator>>(istream & i, Book_Sale_Limit &a);
public:
    Book_Sale_Limit():limit(0)
    {};
    Book_Sale_Limit(int id,int volumn,int pre_price,double d,int l):Book_Sale(id,volumn,pre_price,d),limit(l)
    {

        if(sales_volume>limit)
            gross_sales=original_price*(sales_volume-limit)+real_price*limit;
    };
    Book_Sale_Limit(const Book_Sale_Limit& obj):Book_Sale(obj),limit(obj.limit)
    {
        if(sales_volume>limit)
            gross_sales=original_price*(sales_volume-limit)+real_price*limit;
    };
    Book_Sale_Limit& operator=(const Book_Sale_Limit& a)  //赋值，运算符重载
    {
        if(isbn)
            delete isbn;
        isbn=new(nothrow) char[ibsn_size];
        if(isbn==NULL)
        {
            cerr<<"Something get Wrong!"<<endl;
            exit(EXIT_FAILURE);
        }
        strcpy(isbn,a.isbn);
        this->sales_volume=a.sales_volume;
        this->original_price=a.original_price;
        this->discount=a.discount;
        this->real_price=a.real_price;
        this->gross_sales=a.gross_sales;
        this->limit=a.limit;
        return *this;
    }
    void set(int id,int volumn,int pre_price,int l,double d=1)
    {
        if(id!=-1)
        {
            for(int i=0;i<5;i++)
            {
                char tmp=id%10+'0';
                id/=10;
                isbn[ibsn_size-4-i]=tmp;
            }
        }
        if(volumn!=-1)
            this->sales_volume=volumn;
        if(pre_price!=-1)
            this->original_price=pre_price;
        if(fabs(discount+1)>1e-6)
            this->discount=d;
        if(l!=-1)
            this->limit=l;
        
        Fill();
        if(sales_volume>limit)
            gross_sales=original_price*(sales_volume-limit)+real_price*limit;

    }
    Book_Sale_Limit& operator+=(const int extra_volumn)
    {
        this->sales_volume+=extra_volumn;
        this->gross_sales=this->sales_volume*this->real_price;
        if(sales_volume>limit)
            gross_sales=original_price*(sales_volume-limit)+real_price*limit;
        return *this;
    }

    Book_Sale_Limit& operator-=(const int extra_volumn)
    {
        this->sales_volume-=extra_volumn;
        this->gross_sales=this->sales_volume*this->real_price;
        if(sales_volume>limit)
            gross_sales=original_price*(sales_volume-limit)+real_price*limit;
        return *this;
    }

    void display()
    {
        Book_Sale::display();

        cout<<" ,折扣限制为:"<<limit<<"元"<<endl;
    }
};

istream& operator>>(istream & i, Book_Sale_Limit &a)
{
    int id;
    i>>id;
    for(int j=0;j<5;j++)
    {
        char tmp=id%10+'0';
        id/=10;
        a.isbn[ibsn_size-4-j]=tmp;
    }
    i>>a.sales_volume>>a.original_price>>a.discount>>a.limit;
    a.Fill();
    if(a.sales_volume>a.limit)
            a.gross_sales=a.original_price*(a.sales_volume-a.limit)+a.real_price*a.sales_volume;
    return i;
}

int main()
{
    {
        Book_Sale_Limit b1(95995, 3418, 100, 0.9,3000);
        Book_Sale_Limit b2 = b1;
        Book_Sale_Limit b3;
        b3 = b1;

        cout << "测试初始化，display和cin重载" << endl;

        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:311800元,折扣限制为3000元\n实际为：";
        b1.display();
        cout << "b2应该是同上，实际为：";
        b2.display();
        cout << "b3应该是同上，实际为：";
        b3.display();

        Book_Sale_Limit b4;
        cout << "请输入某书籍销售信息：" << endl;
        cin >> b4;
        cout << "b4应该是您刚输入的信息，实际为：";
        b4.display();

        wait_for_press();
    }

    {
        Book_Sale_Limit b1, b2, b3(95995, 3418, 100, 1,2000);

        cout << "测试set" << endl;

        b1.set(95995, 3418, 100,2000, 0.9);
        b2.set(95995, 3418, 100,2000);
        b3.set(-1, 3500, -1,2500, 0.8);

        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:321800元,折扣限制为2000元\n实际为：";
        b1.display();
        cout << "b2应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:1，现价为:100元，总销售额为:341800元,折扣限制为2000元\n实际为：";
        b2.display();
        cout << "b3应该是该书的ISBN号为:978-7-121-95995-0，销量为:3500本，原价为:100元，折扣为:0.8，现价为:80元，总销售额为:300000元,折扣限制为2500元\n实际为：";
        b3.display();

        wait_for_press();
    }

    {
        Book_Sale_Limit b1(95995, 3418, 100, 0.9,3000);

        cout << "测试重载+=/-=" << endl;

        b1 += 10;
        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3428本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:312800元,折扣限制为3000元\n实际为：";
        b1.display();

        b1 -= 10;
        cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:311800元,折扣限制为3000元\n实际为：";
        b1.display();


        wait_for_press();
    }

    {
        Book_Sale_Limit b1(95994, 3000, 100, 0.8,3000);
        Book_Sale_Limit b2(95996, 4800, 100, 0.5,3000);
        Book_Sale_Limit b3(95998, 2000, 100, 0.9,3000);

        cout << "测试比较运算符" << endl;

        cout << "比较结果应为1，实际为：" << (b1 > b3) << endl;
        cout << "比较结果应为1，实际为：" << (b2 >= b3) << endl;
        cout << "比较结果应为0，实际为：" << (b1 <  b3) << endl;
        cout << "比较结果应为0，实际为：" << (b2 <= b3) << endl;
        cout << "比较结果应为0，实际为：" << (b1 == b2) << endl;
        cout << "比较结果应为0，实际为：" << (b1 != b1) << endl;

        wait_for_press();
    }
    
    return 0;
}