#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thr(void *arg)
{
    printf(" I am a thread ,self = %d\n",pthread_self());
    
    sleep(4);
    printf(" I am a thread ,self = %d\n",pthread_self());
    return NULL;
}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,thr,NULL);
    pthread_detach(tid);//线程分离
    sleep(5);

    void *ret;
    //pthread_join(tid,&ret);//线程回收 但是线程分离以后就不需要了
}
