#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("fd0 = %s\n",ttyname(0));
    printf("fd1 = %s\n",ttyname(1));
    while (1)
    {
        sleep(1);
    }
    
    return 0;
}