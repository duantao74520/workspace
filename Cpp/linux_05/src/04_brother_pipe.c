//兄弟进程通信 哥哥写 弟弟读
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int pipefd[2];
    pipe(pipefd);//建立管道
    pid_t pid ;
    int i;
    for(i = 0;i<2;i++)
    {
        pid =fork();
        if(pid == 0)
        {
            printf("I am a child pid = %d,ppid = %d\n",getpid(),getppid());
            break;
        }
        else if (pid > 0)
        {
            printf("I am a father pid = %d,ppid = %d\n",getpid(),getppid());
        }
        
    }
    if(i==0)//son 1
    {
        printf("I am older brother\n");
        close(pipefd[0]);//关闭读端
        dup2(pipefd[1],STDOUT_FILENO);//重定向
        execlp("ps","ps","aux",NULL);
    }
    else if(i == 1)
    {
        printf("I am younger brother\n");
        close(pipefd[1]);
        dup2(pipefd[0],STDIN_FILENO);
        execlp("grep","grep","aux",NULL);
    }
    else if(i==2)
    {
        printf("I am father \n");
    
        while(1)
        {
            pid_t wpid = waitpid(-1,NULL,WNOHANG);
            if(wpid == -1)
            {
                break;
            }
            if(wpid >0)
            {
                printf("wpid == %d\n",wpid);
            }
        }
        while (1)
        {
          sleep(1);
        }
        

    }
    return 0;
}