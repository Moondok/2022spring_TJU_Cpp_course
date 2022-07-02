

/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
#define ibsn_size 18
#include<stdlib.h>
#include<cmath>
class Book_Sale
{
private:
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
        cout<<"总销售额为:"<<gross_sales<<"元"<<endl;
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

/**********************************************
*
*    TO-DO END
*
***********************************************/

