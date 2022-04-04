/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-04 18:38:04
*LastEditTime: 2022-04-04 19:56:14
*Description: 删除记录，带头节点
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
student* searchbyID(student * head,int query);
bool isContinue();
student * destroy(student * head);


int main()
{
    fstream infile;
    infile.open("D://student/student.txt");
    if(infile.is_open()==0)
    {
        cout<<"fail to open the file!"<<endl;
        return -1;
    }
    student *head=read(infile);
    while (1)
    {
        cout<<"请输入要删除的学生学号: ";
        int query;
        cin>>query;
        student *result=searchbyID(head,query);
        {
            if(result==NULL||result->next==NULL)
                cout<<"Not exist"<<endl;
            else
            {
                student * true_result=result->next;
                result->next=true_result->next;
                delete true_result; 
            }
        }
        /* 执行查询与删除 */
        if (!isContinue())
            break; // 当接收到不需要继续，则退出循环
    }
    /* 退出前打印现有名单 */
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
    student * head=new(nothrow)student;
    if(head==NULL)
    {
        cout<<"内存分配失败！"<<endl;
        exit(0);
    }
    head->next=NULL;
    student *track=head;
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
        track->next=newnode;
        track=newnode;
    }
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


student* searchbyID(student * head,int query)
{//在带头结点的情况里，只要是Null或者下一个结点是NULL就可以判定为不存在
    student *track=head;
    if(track==NULL)
        return track;
    else
    {
        while(track->next)
        {
            if((track->next)->no==query)
                break;
            track=track->next;
        }
        return track;
        
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
*description: 打印一个带头节点的单链表
*param {*}
*return {*}
 **************************************/
void output(student* head)
{
    if(head)
    {
        student *track=head->next;
        while(track)
        {
            cout<<"学号:"<<track->no<<" 姓名:"<<track->name<<" 成绩:"<<track->score<<endl;
            track=track->next;
        }
    }
}
