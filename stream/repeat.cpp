/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-29 22:41:15
*LastEditTime: 2022-05-10 16:29:36
*Description: 
 ***************************************/
#include<iostream>
using namespace std;
istream & f(istream &in)
{
    int n;
    auto in_state = in.rdstate(); // 保存流入函数的状态
    // do something
    
    while(1)
    {
        in>>n;
        if(in.good()&&in.peek()!='.')
        {
            if(n==-1)
                break;
            cout<<n<<endl;
        }
        else if(in.eof()!=1)
        {
            cout<<"illegal"<<endl;
            in.clear();
            char ch;
            while((ch=in.get())!='\n'&&ch!=' ')
                continue;
        }
    }
    in.setstate(in_state);        // 复位流
    return in;
}
int main()
{
    cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
    f(cin);
    return 0;
}

/***************************
 * 我认为setstate()的方法比clear()更好
 * 因为clear()方法无论有无参数，都会影响3个标志位，在设置对应标志位的同时(形参)的同时，也会对另外两个标志位作清除
 * 但setstate()只会对参数中的对应标志位进行设置，不影响其他标志位
 * *************************/