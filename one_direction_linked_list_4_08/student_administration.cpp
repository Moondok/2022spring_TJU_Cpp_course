/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-04 16:15:00
*LastEditTime: 2022-04-04 18:46:41
*Description: 
 ***************************************/
#include<iostream>
#include<fstream>
using namespace std;

/*************结构体****************************/
typedef struct student
{
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
} student;
/**************************************/

/**********函数声明区域*****************/
void menu();
student * read(fstream & infile);
void disp(student * head);
void count(student * head);
int judge_rank(int score);
student* sort(student *head);
int count_num(student * head);
void searchbyID(student* head);
student* search(student * head,int query,bool &tag);
bool isContinue();
void delbyID(student * head);
void modibyID(student *head);
student *  addbyID(student *head);
student * quit(student * head);
/**************************************/

int main()
{
    int choice;
    char ch;
    fstream infile;
    infile.open("D://student/student.txt");
    if(infile.is_open()==0)
    {
        cout<<"Fail to open the file!"<<endl;
        return -1;
    }
    student *head=read(infile);
    
    menu();
    while(true)
    {
        //system("CLS");
        
        cout<<"选择菜单项(0~7): ";
        cin>>choice;
        if (choice == 0) // 选择退出
        {
            std::cout << "\n 确定退出吗?(y/n)" << std::endl;
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
               // quit(*); // 自行设计
                break;
            }
            else
                continue;
        }
        switch(choice)
        {
            case 1:
                disp(head);
                break;
            case 2:
                count(head);
                break;
            case 3:
                head=sort(head);
                disp(head);
                break;
            case 4:
                searchbyID(head);
                break;
            case 5:
                delbyID(head);
                disp(head);
                break;
            case 6: 
                modibyID(head);
                disp(head);
                break;
            case 7:
                head=addbyID(head);
                head=sort(head);
                disp(head);
                break;
            
            default:
                cout<<"\n输入错误,请重新输入"<<endl;
        }
    }
    head=quit(head);
    return 0;
}

/************************************ 
*description: 打印菜单
*param {*}
*return {*}
 **************************************/
void menu()
{
    cout<<endl;
    for(int i=0;i<57;i++)
        cout<<"*";
    cout<<endl;
    cout<<"*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
    cout<<"*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
    cout<<"*\t7 添加记录\t0 退出系统\t\t\t*\n";
    for(int i=0;i<57;i++)
        cout<<"*";
    cout<<endl;
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
*description: 打印链表信息
*param {*}
*return {*}
 **************************************/
void disp(student * head)
{
    cout<<"学生信息汇总如下:"<<endl;
    student * track=head;
    while(track)
    {
        cout<<"学号:"<<track->no<<" 姓名:"<<track->name<<" 成绩:"<<track->score<<endl;
        track=track->next;
    }
    cout<<"=====the end====="<<endl;
}

/************************************ 
*description: 统计信息
*param {*}
*return {*}
 **************************************/
void count(student * head)
{
    int result[5]={0,};

    student * track=head;
    while(track)
    {
        result[judge_rank(track->score)]++;
        track=track->next;
    }
    cout<<"统计信息如下：";
    const char *rank_names[5]={"优","良","中","及格","不及格"};
    
    for(int i=0;i<5;i++)
        cout<<rank_names[i]<<": "<<result[i]<<"人 ";
    cout<<endl;
}

/************************************ 
*description: 根据成绩判断等级
*param {*}
*return {*}
 **************************************/
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

/************************************ 
*description: 对不带头节点的链表进行排序
*param {*}
*return {*}
 **************************************/
student* sort(student *head)
{
    int n=count_num(head);
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
int count_num(student * head)
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
*description: 查找一个学号的信息并返回
*param {*}
*return {*}
 **************************************/
student* search(student * head,int query,bool &tag)
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

/************************************ 
*description: 查找信息
*param {*}
*return {*}
 **************************************/
void searchbyID(student* head)
{
    while (1)
    {
        cout<<"请输入要查找的学号: " ;
        // 程序查询循环
        bool tag=0;
        int query;
        std::cin >> query;
        /* 执行查询 */
        student *result=search(head,query,tag);
        if(!tag)
            cout<<"Not exist"<<endl;
        else 
        {
            if(result==NULL)
                cout<<"学号:"<<head->no<<" 姓名:"<<head->name<<" 成绩:"<<head->score<<endl;
            else
            {
                student * true_result=result->next;
                cout<<"学号:"<<true_result->no<<" 姓名:"<<true_result->name<<" 成绩:"<<true_result->score<<endl;
            }
        }
        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
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

/************************************ 
*description: 删除
*param {*}
*return {*}
 **************************************/
void delbyID(student * head)
{
    while (1)
    {
        cout<<"请输入要删除的学号: ";
        int query;
        cin>>query;
        bool tag=0;
        student *result=search(head,query,tag);
        {
            if(!tag)
                cout<<"Not exist"<<endl;
            else
            {
                if(result==NULL)
                {
                    student *tmp=head->next;
                    delete head;
                    head=tmp;
                }
                else
                {
                    student * true_result=result->next;
                    result->next=true_result->next;
                    delete true_result; 
                }
            }
        }
        /* 执行查询与删除 */
        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
}

/************************************ 
*description: 修改某条记录
*param {*}
*return {*}
 **************************************/
void modibyID(student *head)
{
    while (1)
    {
        cout<<"请输入要修改的成绩的学号: ";
        int query;
        cin>>query;
        bool tag=0;
        student *result=search(head,query,tag);
        {
            if(!tag)
                cout<<"Not exist"<<endl;
            else
            {
                int new_score;
                cin>>new_score;
                if(result==NULL)
                   head->score=new_score;
                else
                {
                    student * true_result=result->next;
                    true_result->score=new_score;
                }
            }
        }
        /* 执行查询与修改 */
        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
}

/************************************ 
*description: 增添记录
*param {*}
*return {*}
 **************************************/
student *addbyID(student * head)
{
    cout<<"请输入要增加的记录的学号: ";
    while (1)
    {
        int query;
        cin>>query;
        bool tag=0;
        student *result=search(head,query,tag);
        {
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
               
        }
        /* 执行查询与增加 */
        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
    return head;
}

/************************************ 
*description: 销毁单链表
*param {*}
*return {*}
 **************************************/
student * quit(student * head)
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