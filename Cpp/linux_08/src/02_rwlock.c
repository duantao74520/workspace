//读写锁的应用


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int beginnum = 1000;
pthread_rwlock_t rwlock= PTHREAD_RWLOCK_INITIALIZER;
void *thr_read(void *arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        int num = (int)arg;
        usleep(2000);
        printf("read thread %d,num = %d\n",num,beginnum); 
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);
        
    }
    return NULL;
}

void *thr_write(void *arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        int num = (int)arg;
        beginnum += 10;
        usleep(2000);
        printf("write thread %d,plus 10 ,num = %d\n",num,beginnum); 
        pthread_rwlock_unlock(&rwlock);
        usleep(6000);
    }
    return NULL;
    
}
int main()
{
    int n =8,i=0;
    pthread_t tid[8] ={0};
    //创建5个读 3个写进程
    for ( i = 0; i < 5; i++)
    {
        pthread_create(&tid[i],NULL,thr_read,(void*)i);
    }
    for(;i<8;i++)
    {
        pthread_create(&tid[i],NULL,thr_write,(void*)i);

    }

    for(i =0 ;i<8;i++)//回收
    {
        pthread_join(tid[i],NULL);
    }
    return 0;
    
}