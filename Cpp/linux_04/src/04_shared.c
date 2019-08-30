#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//父子进程 文件共享
int var = 100;

int main ()
{
    pid_t pid =0;
    pid = fork();
    if(pid == 0)
    {
        printf("var = %d,child,pid = %d,ppid =%d\n",var,getpid(),getppid());
        var =1001;
        printf("var = %d,child ,pid = %d,ppid =%d\n",var,getpid(),getppid());
        sleep(3);
    }
    if(pid >0)
    {
        printf("var = %d ,father,pid = %d,ppid =%d\n",var,getpid(),getppid());
        var =2001;
        printf("var = %d ,father,pid = %d,ppid =%d\n",var,getpid(),getppid());
        sleep(3);
    }
    return 0;

}