#include "mySwap.h"

void mySwap(int &a,int &b)
{
    int c = b;
    b= a;
    a =c;
}

int myAdd(const int &a ,const int &b)
{
    return a+b;
}