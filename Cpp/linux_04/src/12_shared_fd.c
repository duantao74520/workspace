#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc,char *argv[])
{
    if(argc !=2)
    {
        printf("please input file name\n");
        return -1;
    }
    int fd = open(argv[1],O_RDWR|O_CREAT,0666);
    if(fd<0)
    {
        perror("open err");
        exit(1);
    }
    pid_t pid = fork();
    if(pid == 0)//子进程
    {
        write(fd,"hello\n",6);
    }
    else if(pid >0)
    {
        sleep(1);
        write(fd,"hello2\n",7);
        wait(NULL);//等待子进程回收 无返回值 
    }
    return 0;
}