
//创建多个子线程
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thr(void *arg)
{
    int num = (int)arg;
    printf("I am %d thread , self = %lu\n",num,pthread_self());
    
    return (void *)num;
}

int main()
{
    pthread_t tid[5];
    int i ;
    for ( i = 0; i < 5; i++)
    {
        pthread_create(tid+i,NULL,thr,(void*)i);
        sleep(1);

    }
    for ( i = 0; i < 5; i++)
    {
        void *ret;
        pthread_join(tid[i],&ret);//阻塞等待
        printf("i = %d, ret = %d\n",(int)ret);
    }
    
    return 0;
    
}