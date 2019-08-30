//僵尸进程
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int n = 5;
    int i = 0;
    pid_t pid ;
    for(i =0;i<5;i++)
    {
       pid  =fork();
        if(pid ==0)
        {
            break;
        }
        else if(pid >0)
        {

        }
    }
    sleep(i);
    if(i==5)
    {
        for(i=0;i<5;i++){
           pid_t wpid =  wait(NULL);
           printf("wpid = %d\n",wpid);
        }
        while(1)
        {
            sleep(1);
        }
    }
    return 0;
}