/************************************* 
*Author: Kaixu Chen   Moondok
*Date: 2022-04-29 23:12:22
*LastEditTime: 2022-04-29 23:58:05
*Description: 
 ***************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
using namespace std;
void readFromStdin(int * array)
{
    for(int i=0;i<10;i++)
        cin>>array[i];
}
void readFromFile(int * array,FILE* fp)
{
    for(int i=10;i<20;i++)
        fscanf(fp,"%d",&array[i]);
}
void sort(int * array,int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(array[j]>array[j+1])
            {
                int tmp=array[j];
                array[j]=array[j+1];
                array[j+1]=tmp;
            }
        }
    }
}
void outToFile(int *array,int n,FILE* fp)
{
    for(int i=0;i<n;i++)
        fprintf(fp,"%d ",array[i]);

}
int main()
{
    int array[20]={0,};
    readFromStdin(array);
    FILE*fpin=fopen("D:\\1.txt","r");
    if(!fpin)
    {
        cout<<"Fail to open the file!"<<endl;
        exit(EXIT_FAILURE);
    }
    readFromFile(array,fpin);
    fclose(fpin);
    sort(array,20);
    FILE*fpout=fopen("1.out","w");
    if(!fpout)
    {
        cout<<"Fail to open the file!"<<endl;
        exit(EXIT_FAILURE);
    }
    
    outToFile(array,20,fpout);
    fclose(fpout);
    return 0;
}
