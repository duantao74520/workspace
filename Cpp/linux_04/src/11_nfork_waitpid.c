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
        printf("I am parent\n");
        //waitpid 返回值 0代表什么都没动 -1代表子进程都死了
        while(1)
        {
            pid_t wpid = waitpid(-1,NULL,WNOHANG);
            if(wpid ==-1)
            {
                break;
            }
            else if(wpid >0)
            {
                printf("wpid =%d\n",wpid);
            }
        }
        while(1);
        {
            sleep(1);
        }

    }
    return 0;
}