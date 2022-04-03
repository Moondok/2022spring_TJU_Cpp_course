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
        //printf("fail to open the object file!\n");
        exit(1);
    }

    //head node and head pointer
    struct student* head = (struct student*)malloc(sizeof(struct student));
    head->next = NULL;

    int n = 0;

    fscanf(fp, "%d", &n);


    struct student* track = head;
    for (int i = 0; i < n; i++)
    {
        struct student* newnode = (struct student*)malloc(sizeof(struct student));

        fscanf(fp, "%d %s %d", &newnode->no, newnode->name, &newnode->score);

        newnode->next = NULL;
        track->next = newnode;
        track = newnode;
        //printf("%s",newnode->name);
    }
    printf("所有学生的信息如下:\n");
    track = head->next;

    while (track)
    {
        printf("学号:%d 姓名:%s 成绩:%d\n", track->no, track->name, track->score);
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
