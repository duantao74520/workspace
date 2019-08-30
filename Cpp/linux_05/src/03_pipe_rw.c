//子进程写 父进程读 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];//管道
    pipe(pipefd);//创建管道
    printf("pipe id is %d, %d\n",pipefd[0],pipefd[1]);
    pid_t pid =fork();
    if(pid == 0)//子进程
    {
        close(pipefd[0]);//关闭读端
        write(pipefd[1],"hello\n",5);
        //close(pipefd[1]);//关闭写
    }
    else if(pid >0)
    {
        //父进程
        close(pipefd[1]);//写端关闭
        //
        close(pipefd[0]);
        char buf[12] = {0};
        int status;
        wait(&status);
        if(WIFSIGNALED(status))
        {
            printf("kill by %d\n",WTERMSIG(status));
        }
        while(1)
        {
          sleep(1);
        }
        
    }
    return 0;
}