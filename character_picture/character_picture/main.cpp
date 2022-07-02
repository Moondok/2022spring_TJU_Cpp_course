#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
#include"character_picture.h"
using namespace std;


int main()
{
    const char* picture_names[] =
    {
        "classic_picture/airplane.jpg",
        "classic_picture/baboon.jpg",
        "classic_picture/barbara.jpg",
        "classic_picture/cameraman.jpg",
        "classic_picture/compa.png",
        "classic_picture/goldhill.jpg",
        "classic_picture/lena.jpg",
        "classic_picture/lena1.jpg",
        "classic_picture/milkdrop.jpg",
        "classic_picture/peppers.jpg",
        "classic_picture/woman.jpg"

    };
    for(int i=0;i<11;i++)
       CopePicture(picture_names[i]);
    playvedio();

}

ostream& operator<< (ostream& o,const Array& a )
{
    o << "[";
    for (unsigned int i = 0; i < a.shape[a.nowAxis]; i++)
    {
        if (a.nowAxis == a.axisNum - 1)
            o <<setw(5)<< a.data[a.index + i] ;
        else
            o << a[i];
            
        if (a.nowAxis == 0 && a.axisNum > 1 && i != a.shape[a.nowAxis] - 1)
        {
            o << endl;
            o  << " ";
        }
    }

    o << "]";
    if (a.nowAxis == 0)
        o << endl;
    return o;
}