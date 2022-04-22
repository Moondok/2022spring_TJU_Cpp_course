/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-02 17:23:14
*LastEditTime: 2022-04-13 23:55:40
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
void output(student* head);
student* searchbyID(student * head,int query,bool &tag);
bool isContinue();
student * destroy(student *head);
int count(student * head);
student* sort(student *head);

int main()
{
    fstream infile;
    infile.open("D://student.txt",ios::in);
    if(infile.is_open()==0)
    {
        cout<<"fail to open the file!"<<endl;
        return -1;
    }
    student *head=read(infile);
    while (1)
    {
        int query;
        cout<<"请输入需要添加的学生学号:";
        cin>>query;
        bool tag=0;
        searchbyID(head,query,tag);
        if(!tag)
        {
            student * newnode=new student;
            newnode->no=query;
            cin>>newnode->name;
            cin>>newnode->score;
            newnode->next=head;
            head=newnode;
        }
        else
            cout<<"Existed"<<endl;
            

        /* 执行查询与增加 */
        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
    /* 退出前打印排好序的名单 */
    head=sort(head);
    output(head);
    head=destroy(head);
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
    infile.close();
    return head;
}

bool isContinue()
{
    std::cout << "是否继续？(y/n): \n";
    char tmp;
    std::cin >> tmp;
    if (tmp == 'Y' || tmp == 'y')
        return true;

    return false;
}

student* searchbyID(student * head,int query,bool &tag)
{
    //tag专门用来处理头节点，假如tag=1,说明找到了，如果返回NULL就说明没有前驱
    //                     假如tag=0,说明找不到
    student *track=head;
    if(track==NULL)
    {
        tag=0;
        return track;
    }
    else
    {
        tag=0;
        if(head->no==query)
        {
            tag=1;
            return NULL; //意味着没有前驱
        }
        else
        {
            while(track->next)
            {
                if((track->next)->no==query)
                {
                    tag=1;
                    break;
                }
                track=track->next;
            }
            return track;
        }
    }
}

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
        cout<<"学号:"<<track->no<<" 姓名:"<<track->name<<" 成绩:"<<track->score<<endl;
        track=track->next;
    }
}

/************************************ 
*description: 对不带头节点的链表进行排序
*param {*}
*return {*}
 **************************************/
student* sort(student *head)
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