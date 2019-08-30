//利用sigaction 完成捕捉信号 周期性的产生信号  
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void catch_sig(int num)
{
    printf(" catch %d sig\n",num);
}
int main()
{
    //注册一下捕捉函数
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = catch_sig;
    __sigemptyset(&act.sa_mask);
    sigaction(SIGALRM,&act,NULL);//捕捉周期性信号 sigalarm 执行catch_sig
    //setitimer 周期性的发送信号
    struct itimerval myit = {{3,0},{5,0}};
    setitimer(ITIMER_REAL,&myit,NULL);

    while (1)
    {
        printf(" ahahaha \n");
        sleep(1);
    }
    
    return 0;
}