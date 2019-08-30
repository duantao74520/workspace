//把所有常规信号的未决信号集打印至屏幕 ctrl+C来了以后会阻塞 等待处理
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    sigset_t pend,sigproc;
    //设置阻塞信号，等待按键产生信号
    sigemptyset(&sigproc);//先清空
    sigaddset(&sigproc,SIGINT);//SIGINT 是Ctrl+ C命令 加入阻塞集
    //设置阻塞信号集
    sigprocmask(SIG_BLOCK,&sigproc,NULL);// ctrl c被阻塞

    while(1)
    {
        sigpending(&pend);//读取当前未决信号集
        int i= 1;
        for(i = 1;i<32;i++)
            {
                if(sigismember(&pend,i))//判断位图
                {
                    printf("1");
                }
                else
                printf("0");
            }

        printf("\n");
        sleep(1);
    }
    
    
    return 0;
}