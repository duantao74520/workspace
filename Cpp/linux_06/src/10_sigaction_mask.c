//验证mask的作用
//信号不支持排队 
//在运行捕获函数的时候 会阻塞住 相当于说捕获到了一个
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void catch_sig(int num)
{
    printf(" catch %d sig\n",num);
    sleep(5);//执行时间比较长
    printf("end call ,catch sig.\n");
}
int main()
{
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    __sigaddset(&act.sa_mask,SIGQUIT);//临时屏蔽
    act.sa_handler = catch_sig;

    //注册捕捉
    sigaction(SIGINT,&act,NULL);
    while (1)
    {
        printf("ahahhaha\n");
        sleep(1);

    }
    return 0;
}