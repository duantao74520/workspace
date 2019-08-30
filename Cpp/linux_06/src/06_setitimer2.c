//周期性的 timer
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*
typedef void (*sighandler_t)(int);

       sighandler_t signal(int signum, sighandler_t handler);
*/

void catch_sig(int num)
{
    printf("cat %d sig \n",num);
}
int main()
{
    signal(SIGALRM,catch_sig);//第一个是要捕获的信号 第二个是 函数句柄
    struct itimerval myit = {{3,0},{5,0}};
    setitimer(ITIMER_REAL,&myit,NULL);//第一次等待5s 后面是每隔3s
    while(1)
    
    {
        printf("who can kill me\n");
        sleep(1);
    }


    return 0;
}