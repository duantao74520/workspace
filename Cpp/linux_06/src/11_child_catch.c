//利用sigchild信号回收子进程
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
void catch_sig(int num)
{
   pid_t wpid;
   while((wpid = waitpid(-1,NULL,WNOHANG)) >0) //一直等待所有的子进程
   {
       sleep(1);
        if(wpid > 0 )
        {
            printf("wait child %d ok \n",wpid);
        }
   } 
  
}
int main()
{
    int i = 0;
    pid_t pid;
    //在创建子进程的之前屏蔽SIGCHILD信号
    sigset_t myset,oldset;
    __sigemptyset(&myset);
    __sigaddset(&myset,SIGCHLD);

    //oldset 保留现场 

    sigprocmask(SIG_BLOCK,&myset,&oldset);
    for ( i = 0; i < 10; i++)
    {
        pid  = fork();
        if(pid == 0){
            break;

        }

    }
    if(i<10)
    {
        sleep(i);
    }
    if(i == 10)
    {
        struct sigaction act;
        act.sa_flags = 0;
        __sigemptyset(&act.sa_mask);
        act.sa_handler = catch_sig;
        sigaction(SIGCHLD,&act,NULL);

        //解除屏蔽信号
        sigprocmask(SIG_SETMASK,&oldset,NULL);//恢复现场
        while (1)
        {
            sleep(1);
        }
        
    }
    
    return 0;
}