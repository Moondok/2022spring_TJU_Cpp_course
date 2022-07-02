/**********************************************
*
*    TO-DO:
*        请补全该区域的代码，并只提交在这个区域的代码。
*
***********************************************/
//工具函数，判断闰年
bool is_leap(const int year)
{
    return year%400==0||(year%100!=0&&year%4==0);
}



class Date
{
private:
    friend Date operator +(const Date & a,const int b);
    friend Date operator +(const int b,const Date & a);
    friend Date operator -(const Date & a,const int b);

    friend ostream& operator <<(ostream & o,Date & d);
    friend istream & operator>>(istream & i, Date & d);
    int year;
    int month;
    int day;
public:
    Date()
    {
        time_t now=time(0);
        tm * ltm=localtime(&now);
        year=ltm->tm_year+1900;
        month=ltm->tm_mon+1;
        day=ltm->tm_mday;
    }
    Date(const int y,const int m,const int d):year(y),month(m),day(d)
    {}

    //转换构造
    Date(int d)
    {
        if(d>=0)
        {
            int tmp=d;
            int i=1900; //i就是年份
            while(tmp>365+is_leap(i))
            {
                tmp-=(365+is_leap(i));
                i++;
            }
            year=i;
            int j=1;
            int month_table[13]={-1,31,28+is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31};
            while(tmp>month_table[j])
            {
                tmp-=month_table[j];
                j++;
            }
            month=j;
            day=tmp;
        }
        else
        {
            int tmp=d;
            int i=1900;
            while(tmp<0)  //寻找减去d天后的年份
            {
                i--;
                tmp+=(365+is_leap(i));
                
            }
            year=i;
            //现在要从i年1月1日起算向后数tmp天（注意0天是保持不变，1天是向后一天，和其他地方略有区别）
            //因此给tmp加一个1
            tmp++;
            int j=1;
            int month_table[13]={-1,31,28+is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31};
            while(tmp>month_table[j])
            {
                j++;
                tmp-=month_table[j];
            }
            month=j;
            day=tmp;
        }
    }
    
    //类型转换函数
    explicit operator int ()
    {
        int tmp=0;
        int month_table[13]={-1,31,28+is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31};
        if(this->year>=1900)  //说明tmp是正数
        {
            for(int i=1900;i<this->year;i++)
                tmp+=365+is_leap(i);
            //进入当年
            
            for(int i=1;i<this->month;i++)
                tmp+=month_table[i];
            
            //进入当月
            tmp+=this->day;
        }
        else  //说明tmp是负数
        {
            //先算到下月1号有多少天
            tmp+=month_table[this->month]-this->day+1;
            //再算到下一年1号有多少天
            for(int i=this->month+1;i<=12;i++)
                tmp+=month_table[i];
            //最后算下一年第一天到1900年第一天
            for(int i=this->year+1;i<1900;i++)
                tmp+=365+is_leap(i);
            //由于该日期小于1900，因此为负数
            tmp=-tmp;

        }
        return tmp;

    }

    void set( int y,int m=1,int d=1)
    {
        if(y)
            year=y;
        if(m)
            month=m;
        if(d)
            day=d;
    }

    Date & operator++ ()
    {
        int month_table[13]={-1,31,28+is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31};
        if(this->day==month_table[this->month])
        {
            if(this->month==12)
            {
                Date::set(this->year+1,1,1);
            }
            else
                Date::set(this->year,this->month+1,1);
        }
        else
            this->day++;
        return * this;
    }

    Date & operator-- ()
    {
        int month_table[13]={-1,31,28+is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31};
        if(this->day==1)
        {
            if(this->month==1)
            {
                Date::set(this->year-1,12,31);
            }
            else
                Date::set(this->year,this->month-1,month_table[this->month-1]);
        }
        else
            this->day--;
        return * this;
    }

    Date operator++(int )
    {
        int month_table[13]={-1,31,28+is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31};
        Date tmp(this->year,this->month,this->day);
        if(this->day==month_table[this->month])
        {
            if(tmp.month==12)
            {
                Date::set(this->year+1,1,1);
            }
            else
                Date::set(this->year,this->month+1,1);
        }
        else
            Date::set(this->year,this->month,this->day+1);
        
        return tmp;
    }

    Date operator--(int )
    {
        int month_table[13]={-1,31,28+is_leap(this->year),31,30,31,30,
                             31,31,30,31,30,31};
        Date tmp(this->year,this->month,this->day);
        if(this->day==1)
        {
            if(this->month==1)
            {
                Date::set(this->year-1,31,31);
            }
            else
                Date::set(this->year,this->month-1,month_table[this->month-1]);
        }
        else
            Date::set(this->year,this->month,this->day-1);
        
        return tmp;
    }

    bool operator>(const Date& b)const
    {
        if(this->year>b.year)
            return true;
        if(this->month>b.month)
            return true;
        if(this->day>b.day)
            return true;

        return false;
    }
    bool operator<(const Date& b)const
    {
        if(this->year<b.year)
            return true;
        if(this->month<b.month)
            return true;
        if(this->day<b.day)
            return true;

        return false;
    }


    bool operator>=(const Date& b)const
    {
        return !(*this<b);
    }

    
    bool operator<=(const Date& b)const
    {

        return !(*this>b);
    }

    bool operator==(const Date& b)const
    {
        if(this->year==b.year&&this->month==b.month&&this->day==b.day)
            return true;
        return false;
    }

    bool operator!=(const Date& b)const
    {
        return !(*this==b);
    }
    
    Date & operator+=(const int b)
    {
        Date tmp=*this+b;
        Date::set(tmp.year,tmp.month,tmp.day);
        return *this;
    }

    Date & operator-=(const int b)
    {
        Date tmp=*this-b;
        Date::set(tmp.year,tmp.month,tmp.day);
        return *this;
    }

};


ostream& operator <<(ostream & o,Date & d)  //流插入的重载
{
    o<<d.year<<"年"<<d.month<<"月"<<d.day<<"日"<<endl;
    return o;
}

istream & operator>>(istream & i, Date & d)  //流提取的重载
{
    i>>d.year>>d.month>>d.day;
    return i;
}

Date operator +(const Date & a,const int b)//+的第一个重载
{
    if(b>=0)
    {
        Date tmp;
        int tem=b;
        int month_table[13]={-1,31,28+is_leap(a.year),31,30,31,30,
                             31,31,30,31,30,31};
        int i=a.year;
        int j=a.month;
        int k=a.day;
        if(tem>month_table[a.month]-a.day)  //跨了月
        {
            if(j!=12)
            {
                j++;
            }
            else
            {
                i++;
                j=1;

            }
            k=1;
            tem-=(month_table[a.month]-a.day);//不-1是因为直接跨到了下个月1号，按照从1号起算的方式来

            //看在第i年能不能控制住
            while(tem>month_table[j]&&j<=12)
            {
                tem-=month_table[j];
                j++;
            }

            if(j==13) //第i年没控制住
            {
                j=1;
                i++;
                while(tem>365+is_leap(i))
                {
                    tem-=(365+is_leap(i));
                    i++;
                }
                
                int j=1;
                int month_table[13]={-1,31,28+is_leap(i),31,30,31,30,
                             31,31,30,31,30,31};
                while(tem>month_table[j])
                {
                    tem-=month_table[j];
                    j++;
                }
                tmp.set(i,j,tem);
                return tmp;
                
            }
            else
            {
                tmp.set(i,j,tem);
                return tmp;
            }

        }
        else
        {
            tmp.set(i,j,k-b);
            return tmp;
        }

    }
    else
        return a-b;
}

Date operator +(const int b,const Date & a)
{
    return a+b;
}

Date operator -(const Date & a,const int b)
{
    if(b>0)
    {
        if(a.day>b)  //说明没出月
        {
            Date tmp(a.year,a.month,a.day-b);
            return tmp;
        }
        else//出了月份
        {
            int i=a.year;
            int j=a.month;
            
            int tem=b;

            tem-=(a.day-1);  //来到了当月1号
            if(j==1)
            {
                j=12;
                i--;
            }
            else
                j--;

            int month_table[13]={-1,31,28+is_leap(i),31,30,31,30,
                             31,31,30,31,30,31};
            while(tem>month_table[j]&&j>=1)
            {
                tem-=month_table[j];
                j--;
                
            }
            if(j==0)  //说明退到了前一年
            {
                i--;
                int tmp=-tem;
                while(tmp<0)  //寻找减去d天后的年份
                {
                    tmp+=(365+is_leap(i));
                    if(tmp>=0)
                        break;
                    i--;
                }
                
                //现在要从i年1月1日起算向后数tmp天（注意0天是保持不变，1天是向后一天，和其他地方略有区别）
                //因此给tmp加一个1
                tmp++;
                int j=1;
                int month_table[13]={-1,31,28+is_leap(i),31,30,31,30,
                             31,31,30,31,30,31};
                while(tmp>month_table[j])
                {
                    tmp-=month_table[j];
                    j++;
                }
                return Date(i,j,tmp);
            }
            else
            {
                return Date(i,j,month_table[j]-tem+1);
            }
            
        }
    }
    else
        return a+(-b);
}

int operator -(Date a,Date b)
{
    int d1=(int)a;
    int d2=(int)b;
    return d1-d2;
}


/**********************************************
*
*    TO-DO END
*
***********************************************/

