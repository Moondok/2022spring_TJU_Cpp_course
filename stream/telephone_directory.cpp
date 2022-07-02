#include<iostream>
#include<sstream>
#include<stdlib.h>
#include<fstream>
using namespace std;

/************************************ 
*description: 在字符串流中检测待查值target,查找成功返回tag=1和答案ans
*param {*}
*return {*}
 **************************************/
void valid(stringstream & instr, const int target, bool & tag,long long int &ans);

/************************************ 
*description: 检测输入参数合法性，返回待查值target和文件流in
*param {*}
*return {*}
 **************************************/
bool CheckEligibility(int argc,char*argv[],ifstream & in,int &target);

/************************************ 
*description: 将文件流内容读入字符串流
*param {*}
*return {*}
 **************************************/
void ReadInStr(ifstream &infile,stringstream & instr);

#include<time.h>
int main(int argc ,char*argv[])
{
    /*
    clock_t start = clock();*/
    ifstream infile;
    int target;
    if(!CheckEligibility(argc,argv,infile,target)) //检查参数
        return -1;
    
    stringstream instr;
    ReadInStr(infile,instr);   //将文件流读入字符串流

    long long int ans=0;
    bool tag=0;
    valid(instr,target,tag,ans); //在文件流中检测答案

    if(tag)
        cout<<ans<<endl;  //若答案存在,tag为1，输出

    /*
    clock_t end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
    */

    return 0;
}

void valid(stringstream & instr, const int target, bool & tag,long long int &ans)
{
    long long int n;
    string tem;
    instr.seekg(0,ios::beg);
    while(instr.eof()!=1)
    {
        instr>>n;
        if(instr.good()==0)
        {
            instr.clear();
            instr>>tem;
        }
        else if((n/100000000==target&&!tag)||(n/100000000==target&&n>ans))
        {
            tag=1;
            ans=n;
        }
    }
}

bool CheckEligibility(int argc,char*argv[],ifstream & in,int &target)
{
    bool re=1;
    if (argc != 3) 
    {
        cerr << "请给出文件名和前三位号码" << endl;
        return 0;
    }
    in.open(argv[1]);
    if (!in) {
        cerr << "无法打开输入文件" << endl;
        return 0;
    }
    istringstream param(argv[2]);
    param>>target;
    if(target/100<1||target/100>2)
    {
        cerr<<"待查前三位错误"<<endl;
        return 0;
    }
    return re;
}

void ReadInStr(ifstream &infile,stringstream & instr)
{
    string tmp;
    while(infile.peek()!=EOF)
    {
        infile>>tmp;
        instr<<tmp<<" ";
    }
    infile.close();
}
