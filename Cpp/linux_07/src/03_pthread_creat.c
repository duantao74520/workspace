//创建一个线程
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *thr(void *arg)
{
    printf("I am a thread,pid = %d,tid = %lu\n",getpid(),pthread_self());
    return NULL;
}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,thr,NULL);
    printf("I am a main thread,pid = %d,tid = %lu\n",getpid(),pthread_self);
    sleep(1);
    return -1;
}