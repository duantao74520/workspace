//父子进程实现ps aux|grep bash
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if(pid == 0)//son
    {   close(fd[0]);//关闭读
        //用son --> ps 显示到屏幕 则需要重定向
    //1.重定向
        dup2(fd[1],STDOUT_FILENO);//标准输出重定向到管道写端，这样ps显示的值放到管道
        execlp("ps","ps","aux",NULL);
    }
    else if(pid >0)//parent
    {
        close(fd[1]);//单向
        //1.先重定向，标准输入重定向到管道读
        dup2(fd[0],STDIN_FILENO);
        //2.execlp
        execlp("grep","grep","bash",NULL);//输入是屏幕上 但是重定向到管道了 grep就读管道的数
    }
    return 0;
}