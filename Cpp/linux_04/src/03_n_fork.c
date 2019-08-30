//创建n个子进程
//子进程需要break 防止子进程再裂化进程 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
    int n = 5;
    int i =0;
    pid_t pid =0;
    for(i =0;i<5;i++)//父进程在循环结束
    {
        pid = fork();
        if(pid == 0)
        {
            sleep(1);
          //  printf("I am child ,pid = %d,ppid =%d\n",getpid(),getppid());
            break;//子进程退出循环 防止再fork
        }
        if(pid >0)
        {
            printf("I am a father ,pid = %d,ppid =%d \n",getpid(),getppid());
            sleep(1);
        }

    }
    sleep(i);//按i的值来确定子进程 因为break了
    if(i<5)
    {
        printf(" i = %d\n",i);
        printf("I am a child ,will exit ,pid = %d,ppid =%d\n",getpid(),getppid());
    }
    else
    {
        printf("I am a father ,will out ,pid = %d,ppid =%d\n",getpid(),getppid());
    }
    
    while(1);
    return 0;

}