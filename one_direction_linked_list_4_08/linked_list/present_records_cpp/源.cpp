/*************************************
*Author: Kaixu Chen   Moondok
*Date: 2022-03-28 09:56:25
*LastEditTime: 2022-03-28 10:29:36
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
    infile.open("D://student/student.txt", ios::in);
    if (infile.is_open() == 0)
    {
        cout << "fail to open the file!" << endl;
        return -1;
    }
    int n = 0;
    infile >> n;
    student* head = new (nothrow) student;
    head->next = NULL;

    student* track = head;  //working pointer
    for (int i = 0; i < n; i++)
    {
        student* newnode = new (nothrow) student;
        infile >> newnode->no >> newnode->name >> newnode->score;
        newnode->next = NULL;
        track->next = newnode;
        track = newnode;
    }

    //output
    cout << "所有学生的信息如下:" << endl;
    track = head->next;
    student* track2 = track;
    while (track)
    {
        cout << "学号:" << track->no << " 姓名:" << track->name << " 成绩:" << track->score << endl;
        track = track->next;
        delete track2;
        track2 = track;
    }
    delete head;  //删掉头指针
    infile.close();
    return 0;
}

