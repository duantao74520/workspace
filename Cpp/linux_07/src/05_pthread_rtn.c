//线程回收
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *thr(void *arg)
{
   
    printf("I am a thread,pid = %d,tid = %lu\n",getpid(),pthread_self());
    return (void *)100;
}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,thr,NULL);
    void *ret;
    pthread_join(tid,&ret);
    printf("ret is %d\n",(int)ret);
    pthread_exit(NULL);

}