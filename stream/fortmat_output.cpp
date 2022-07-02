/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-29 21:15:25
*LastEditTime: 2022-05-09 19:03:10
*Description: 
 ***************************************/
#include<iostream>
#include<iomanip>
using namespace std;

typedef struct node
{
    double data=0;
    node* next=NULL;
}node;

int get_length(double d)
{
    int cnt=0;
    if(d<0)
        cnt=1;
    while(true)
    {
        d=d/10;
        cnt++;
        if(int(d)==0)
            break;
    }
    return cnt;
}

node* destroy(node* head)
{
    node*track=head->next;
    node*track2=head;
    while(track)
    {
        delete track2;
        track2=track;
        track=track->next;
    }
    delete track2;
    return NULL;
}
int main()
{
    double d;
    node * head=new(nothrow)node;
    node * track=head;
    if(head==NULL)
    {
        cout<<"fail to allocate memeory!"<<endl;
        exit(1);
    }
    int length=0;
    while(1)
    {
        cin>>d;
        if(cin.good()==0)
            break;
        node*newnode=new(nothrow)node;
        if(newnode==NULL)
        {
            cout<<"fail to allocate memeory!"<<endl;
            exit(1);
        }
        if(d<0)
            d+=0.0005;
        else
            d-=0.0005;
        newnode->data=d;
        int clength=get_length(d);
        if(clength>length)
            length=clength;
        track->next=newnode;
        track=newnode;
    }
    track=head->next;
    while(track)
    {
        cout<<setw(length+4)<<setiosflags(ios::fixed)<<setprecision(3)<<track->data<<endl;
        track=track->next;
    }
    head=destroy(head);
    return 0;
}
