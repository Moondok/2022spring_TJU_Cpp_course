/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-02 10:50:29
*LastEditTime: 2022-04-13 23:38:36
*Description: 
 ***************************************/
#include<iostream>
#include<fstream>
using namespace std;

typedef struct student
{
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
} student;

student * read(fstream & infile);
student* my_bubble_sort(student *head);
int count(student * head);
void output(student* head);
student * destroy(student * head);

int main()
{
    fstream infile;
    infile.open("D://student.txt",ios::in);
    if(infile.is_open()==0)
    {
        cout<<"fail to open the file!"<<endl;
        return -1;
    }
    student* head=read(infile);  //读入
    head=my_bubble_sort(head);  //排序
    output(head);  //打印结果
    head=destroy(head);  //销毁
    infile.close();
    return 0;
}

/************************************ 
*description: 将文件中的数据读入链表中
*param {*}
*return {*}
 **************************************/
student * read(fstream & infile)
{
    int n=0;
    infile>>n;
    student * head=NULL;
    student *track=NULL;
    for(int i=0;i<n;i++)
    {
        student* newnode= new(nothrow) student;
        if(newnode==NULL)
        {
            cout<<"内存分配失败！"<<endl;
            return NULL;
        }
        infile>>newnode->no>>newnode->name>>newnode->score;
        newnode->next=NULL;
        if(i==0)
            head=newnode;
        else
            track->next=newnode;
        track=newnode;
    }
    return head;
}

/************************************ 
*description: 对不带头节点的链表进行排序
*param {*}
*return {*}
 **************************************/
student* my_bubble_sort(student *head)
{
    int n=count(head);
    for(int i=0;i<n-1;i++)
    {
        student* track=head; //这个结点记录front 结点前一个结点；
        student* front=head;
        student* behind=head->next; //这里写没什么问题,当n==1时，压根进不来循环
        for(int j=0;j<n-i-1;j++)
        {
            if(front->score<behind->score||(front->score==behind->score&&front->no>behind->no))
            {
                if(j==0)  //第一个结点比第二个结点小
                {
                    front->next=behind->next;
                    behind->next=front;
                    head=behind;
                    behind=front->next;
                    front=head->next;
                    track=head;
                }
                else
                {
                    track->next=behind;
                    front->next=behind->next;
                    behind->next=front;
                    behind=front->next;
                    track=track->next;
                }
            }
            else
            {
                if(j!=0)
                    track=track->next;
                front=front->next;
                behind=behind->next;
            }
        }
    }
    return head;
}

/************************************ 
*description: 求解不带头节点的链表的结点个数
*param {*}
*return {*}
 **************************************/
int count(student * head)
{
    student * track=head;
    int n=0;
    while(track)
    {
        n++;
        track=track->next;
    }
    return n;
}

/************************************ 
*description: 打印一个不带头节点的单链表
*param {*}
*return {*}
 **************************************/
void output(student* head)
{
    student *track=head;
    while(track)
    {
        cout<<track->no<<" "<<track->name<<" "<<track->score<<endl;
        track=track->next;
    }
}

/************************************ 
*description: 销毁一个单链表
*param {*}
*return {*}
 **************************************/
student * destroy(student * head)
{
    student * front =head;
    if(front==NULL)
        return NULL;
    student * behind=head->next;
    while(behind)
    {
        delete front ;
        front= behind;
        behind=behind->next;
    }
    delete front;
    return NULL;
}
