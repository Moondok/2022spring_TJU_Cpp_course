#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
using namespace std;

bool CheckEligibility(int argc,char*argv[],ifstream &infile,char* outfilename);

void Denoise(const char * outfilename,ifstream & infile);

int main(int argc,char*argv[])
{
    char outfilename[20]={'\0'};
    ifstream infile;
    if(!CheckEligibility(argc,argv,infile,outfilename))
        return -1;
    cout<<outfilename;
    Denoise(outfilename,infile);

    return 0;
}

bool CheckEligibility(int argc,char*argv[],ifstream &infile,char* outfilename)
{
    
    bool re=1;
    if (argc != 2) 
    {
        cerr << "请确保输入参数正确" << endl;
        return 0;
    }
    infile.open(argv[1]);
    if (!infile) 
    {
        cerr << "无法打开输入文件" << endl;
        return 0;
    }
    int slash_pos=0;//截取文件名字，找到'\'的位置
    int point_pos=0;
    for(int i=0;argv[1][i]!='\0';i++)
    {
        if(argv[1][i]=='\\'||argv[1][i]=='/')
            slash_pos=i;
        if(argv[1][i]=='.')
            point_pos=i;
    }

    for(int i=slash_pos+1;i<point_pos;i++)
        outfilename[i-slash_pos-1]=argv[1][i];
    strcat(outfilename,"_red");
    for(int i=point_pos;argv[1][i]!='\0';i++)
        outfilename[i-slash_pos+3]=argv[1][i];
    return re;
}

void Denoise(const char * outfilename,ifstream & infile)
{
    ofstream outfile(outfilename);
    if(outfile.is_open()==0)
    {
        cerr<<"Fail to create file!"<<endl;
        exit(EXIT_FAILURE);
    }

    char tmp;
    while(infile.peek()!=EOF)
    {
        
        if(infile.tellg()%3==0)
        {
            infile.get(tmp);
            outfile.put(tmp);
        }
        else
            infile.get(tmp);
    }
    infile.close();
    outfile.close();
}