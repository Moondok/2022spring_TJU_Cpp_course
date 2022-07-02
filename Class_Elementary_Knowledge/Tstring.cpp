#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string.h>

using namespace std;

class TString
{
private:
    char *content;        //指向字符串的指针
    int   len;            //字符串的长度，不含尾零
public:
    TString(char *s = NULL);
    TString(const TString &);
    ~TString();
    char *get_content();
    void set(char *s = NULL);
    void set(const TString &);
    int length();
};


TString::TString(char*s)
{
    if(s==NULL)
    {
        content=NULL;
        len=0;
    }
    else
    {
        len=static_cast<int>(strlen(s));
        content=new char [len+1];
        content[len]='\0';
        strcpy(content,s);
    }
}

TString:: TString(const TString& s)
{
    if(s.len==0)
    {
        this->len=s.len;
        this->content=NULL;
    }
    else
    {
        this->len=s.len;
        this->content=new char [len+1];
        this->content[len]='\0';
        strcpy(this->content,s.content);
    }
}

TString::~TString()
{
    if(this->content)
        delete this->content;
    this->content=NULL;
    this->len=0;
}

char * TString:: get_content()
{
    return content;
}

void TString::set(char *s)
{
    if(s==NULL)
    {
        if(this->content)
            delete this->content;
        this->content=NULL;
        this->len=0;
    }
    else
    {
        this->len=static_cast<int>(strlen(s));
        if(this->content)
            delete this->content;
        this->content=new char [len+1];
        this->content[len]='\0';
        strcpy(this->content,s);
    }
}

void TString::set(const TString &s)
{
    if(s.len==0)
    {
        if(this->content)
            delete this->content;
        this->len=s.len;
        this->content=NULL;
    }
    else
    {
        if(this->content)
            delete this->content;
        this->len=s.len;
        this->content=new char [len+1];
        this->content[len]='\0';
        strcpy(this->content,s.content);
    }
}

int TString:: length()
{
    return this->len;
}













