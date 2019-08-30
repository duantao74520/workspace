#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    struct itimerval myit = {{0,0},{3,0}};//定义3s以后发送SIGALRM信号
    setitimer(ITIMER_REAL,&myit,NULL);
    while(1)
    {
        sleep(1);
        printf("ahhahah\n");
    }
    return -1;
}