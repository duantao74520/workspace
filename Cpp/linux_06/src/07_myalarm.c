//利用seitimer实现alarm

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

unsigned int myalarm(unsigned int seconds)
{
    struct  itimerval myit = {{0,0,},{0,0}},oldit;
    myit.it_value.tv_sec = seconds;
    setitimer(ITIMER_REAL,&myit,&oldit);//设置alarm时间 为seconds
    return oldit.it_value.tv_sec;//返回剩余时间
}
int main()
{
    int ret;
    ret = myalarm(5);
    printf("ret = %d\n",ret);
    sleep(2);
    ret = myalarm(3);
    printf("ret = %d\n",ret);
    while(1)
    {
        sleep(1);
        printf("hahhaha\n");
    }
    return 0;
}