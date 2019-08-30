#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *thr(void *arg)
{
    while(1)
    {
            printf("I am a thread ,pid = %d,tid = %d\n",getpid(),pthread_self());
        sleep(1);
    }
    return (void*)100;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,thr,NULL);
    sleep(5);
    pthread_cancel(tid);//杀死线程 外部杀死
    void *ret;
    pthread_join(tid,&ret);//回收线程
    return 0;
}