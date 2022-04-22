/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-17 11:07:26
*LastEditTime: 2022-04-17 12:39:09
*Description: 
 ***************************************/
#include<iostream>
using namespace std;
void itobs(int num,char *buffer)
{
    int tmp;
    for(int i=0;i<32;i++)
    {
        tmp=num;
        tmp=tmp>>(32-1-i);
        tmp=tmp&0x0001;
        //cout<<tmp<<endl;
        buffer[i+i/8]=(tmp==1)+'0';
    }
}
int main()
{
    cout<<"please input some integers:"<<endl;
    int num;
    while(true)
    {
        cin>>num;
        if(cin.good()==0)
            break;
        else
        {
            char str[36];
            str[35]='\0';
            str[8]=str[17]=str[26]=' ';
            itobs(num,str);
            cout<<"the binary form of "<<num<<" is:"<<endl;
            cout<<str<<endl;
        }
    }
}