#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    printf("Begin .. \n");//注意缓冲区的问题 \n才输出的
    pid_t pid = fork();//创建子进程
    printf("pid = %d \n",pid);
    if(pid <0 )
    {
        perror("fork err");
        exit(1);
    }
    if(pid == 0 )//代表是子进程
    {
        while(1)
        {
        printf("i am a child ,pid = %d,ppid = %d\n",getpid(),getppid());
        sleep(1);
        }
    }
    else if(pid > 0 )//代表是子进程
    {
        while(1)
        {
        printf("i am a parent id ,child id = %d ,pid = %d,ppid = %d\n",pid ,getpid(),getppid());
        sleep(1);//防止孤儿进程
        }
        
     }
    printf("End....\n");
    return 0;
}