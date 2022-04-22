/*
 * @Author: Kaixu Chen   Moondok
 * @Date: 2022-03-28 08:51:32
 * @LastEditTime: 2022-04-13 23:30:35
 * @Description: 
 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
    /*! 不允许修改上述结构 !*/
};
int main()
{
    FILE* fp = NULL;
    fp = fopen("D://student.txt", "r");

    if (fp == NULL)
    {
        printf("fail to open the object file!\n");
        exit(1);
    }

    int n = 0;

    fscanf(fp, "%d", &n);
    struct student* head=NULL,*track=NULL;
    for (int i = 0; i < n; i++)
    {
        struct student* newnode = (struct student*)malloc(sizeof(struct student));

        fscanf(fp, "%d %s %d", &newnode->no, newnode->name, &newnode->score);

        newnode->next = NULL;
        if(i==0)
        {
            head=newnode;
            track=head;
        }
        else
        {
            track->next = newnode;
            track=newnode;
        }
        //printf("%s",newnode->name);
    }
    printf("所有学生的信息如下:\n");
    track = head;

    while (track)
    {
        printf("%d %s %d\n", track->no, track->name, track->score);
        track = track->next;
    }
    //释放
    track=head;
    struct student *track2=track;
    while(track)
    {
        track=track->next;
        free(track2);
        track2=track;
    }
    head=NULL;
    fclose(fp);
    return 0;
}
