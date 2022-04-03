/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-03-28 11:17:35
*LastEditTime: 2022-04-02 10:53:10
*Description: 
 ***************************************/
#include<iostream>
#include<fstream>
using namespace std;

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
};

int judge_rank(int score)
{
    int rank=0;
    int a=score/10;
    switch(a)
    {
        case 10:
        case 9:
            rank=0;
            break;
        case 8:
            rank=1;
            break;
        case 7:
            rank=2;
            break;
        case 6:
            rank=3;
            break;
        default:
            rank=4;
            break;
    }
    return rank;
}
student *read(fstream &infile)
{
    int n=0;
    infile>>n;
    student *head =new (nothrow) student;
    if(head==NULL)
    {
        cout<<"内存申请失败！"<<endl;
        exit(0);
    }
    head->next=NULL;
    student*track =head;  //working pointer
    for(int i=0;i<n;i++)
    {
        student * newnode =new (nothrow) student;
        if(newnode ==NULL)
        {
            cout<<"内存申请失败！"<<endl;
            exit(0);
        }
        infile>>newnode ->no>>newnode->name>>newnode->score;
        newnode->next=NULL;
        track->next=newnode;
        track=newnode;
    }
    return head;
}

int main()
{
    fstream infile;
    infile.open("D://student/student.txt",ios::in);
    if(infile.is_open()==0)
    {
        cout<<"fail to open the file!"<<endl;
        return -1;
    }
    
    student *head=read(infile); 

    int result[5]={0,};

    student *track=head->next;
    student *track2=track;

    while(track)
    {
        result[judge_rank(track->score)]++;
        track=track->next;
        delete track2;
        track2=track;
    }
    delete head;

    cout<<"统计信息如下：";
    const char *rank_names[5]={"优","良","中","及格","不及格"};
    
    for(int i=0;i<5;i++)
    {
        cout<<rank_names[i]<<": "<<result[i]<<"人 ";
    }
    cout<<endl;
    return 0;
}
