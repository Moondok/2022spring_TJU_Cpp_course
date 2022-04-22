/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-03-28 09:56:25
*LastEditTime: 2022-04-13 23:32:07
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

int main()
{
    fstream infile;
    infile.open("D://student.txt",ios::in);
    if(infile.is_open()==0)
    {
        cout<<"fail to open the file!"<<endl;
        return -1;
    }
    int n=0;
    infile>>n;
    student *head=NULL,*track=NULL;
    
    for(int i=0;i<n;i++)
    {
        student * newnode =new (nothrow) student;
        if(newnode==NULL)
        {
            cout<<"fail to allocate memory!"<<endl;
            return -1;
        }
        infile>>newnode ->no>>newnode->name>>newnode->score;
        newnode->next=NULL;
        if(i==0)
            head=track=newnode;
        
        else
        {
            track->next=newnode;
            track=newnode;
        }
    }

    //output
    cout<<"所有学生的信息如下:"<<endl;
    track=head;
    student *track2=track;
    while(track)
    {
        cout<<track->no<<" "<<track->name<<"  "<<track->score<<endl;
        track=track->next;
        delete track2;
        track2=track;
    } 
    infile.close();
    return 0;
}

