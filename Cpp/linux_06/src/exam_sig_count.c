//父子进程循环报数
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
int count = 0;
int kidpid =0;
void fatherPrintf(int num)
{
    printf("father : %d\n",count);
    count+=2;
    kill(kidpid , SIGUSR1);
}
void kidPrintf(int num)
{
    printf("kid : %d\n",count);
    count +=2;
    kill(getppid(),SIGUSR2);


}
int main()
{
    pid_t pid;
    pid = fork();//创建子进程
    if(pid == 0)
    {
        //子进程
        count = 0;
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = kidPrintf;
        __sigemptyset(&act.sa_mask);
        //sigaction(SIGUSR1,&act,NULL);
        signal(SIGUSR1,kidPrintf);
        while (1)
        {
            sleep(1);
        }
        

    }
    else if(pid >0)
    {
        //父进程
        sleep(1);
        kidpid = pid;
        count = 1;
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = fatherPrintf;
        __sigemptyset(&act.sa_mask);
        kill(kidpid , SIGUSR1);
        sigaction(SIGUSR2,&act,NULL);
        while (1)
        {
            sleep(1);
        }
        

    }
    return 0;
}