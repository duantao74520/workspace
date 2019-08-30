//子进程写 父进程读
#include <stdio.h>
#include <unistd.h>

int main()
{
    int pipefd[2];//管道
    pipe(pipefd);//创建管道
    printf("pipe id is %d, %d\n",pipefd[0],pipefd[1]);
    pid_t pid =fork();
    if(pid == 0)//子进程
    {
        write(pipefd[1],"hello\n",5);
    }
    else if(pid >0)
    {
        //父进程
        char buf[12] = {0};
        //如果没有设置 O_NONBLOC标志 则表示是阻塞模式
        int ret = read(pipefd[0],buf,sizeof(buf));//读设备的时候 是阻塞等待的 读文件不是
        if(ret >0)
        {
            write(STDOUT_FILENO,buf,ret);
        }
    }
    return 0;
}