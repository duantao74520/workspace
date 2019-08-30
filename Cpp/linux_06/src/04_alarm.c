#include <stdio.h>
#include <unistd.h>

int main()
{
    alarm(6);
    int i;
    while(1)
    {
      i++;
    }
    printf(i);
    return 0;

}