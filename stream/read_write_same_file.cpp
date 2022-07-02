#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
int main()
{
    fstream infile("foo.bar",ios::in|ios::out);
    if(infile.is_open()==0)
    {
        cerr<<"Fail to open the object file!"<<endl;
        return -1;
    }
    int n=0;
    char ch;
    while(infile.peek()!=EOF)
    {
        ch=infile.get();
        if(ch=='\n')
            n++;
    }
    infile.clear();
    if(ch!='\n')
    {
        infile<<'\n';
        n++;
    }
    long long int *array=new long long int[n];
    
    int pos=1;
    array[0]=0;
    infile.clear();
    infile.seekp(0,ios::beg);
    //cout<<infile.tellg()<<endl;
    long long int track=0;
    while(pos<=n)
    {
        ch=infile.get();
        track++;
        if(ch=='\n')
            array[pos++]=track;
    }
    cout<<track<<endl;
    
    infile.seekp(0,ios::end);
    infile<<n;
    
    for(int i=0;i<=n;i++)
        infile<<" "<<array[i];
    infile.close();
    delete[]array;
    
    return 0;
}