//用信号量完成生产者 消费者模型
//定义blank xful 最多只能有几个 用两个信号量进行同步
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t blank,xfull;//两个信号量
#define _SEM_CNT_ 5
int queque[_SEM_CNT_];//模拟饼框
int beginnum =100;

void *thr_product(void *arg)
{
    int i;
    while (1)
    {
        sem_wait(&blank);
        printf("------%s----self-%lu---num---%d---\n",__FUNCTION__,pthread_self(),beginnum);
        queque[(i++)%_SEM_CNT_] = beginnum++;
        sem_post(&xfull);
        sleep(rand()%2);
    }
    
    return NULL;

}
void *thr_consumer(void *arg)
{
    int i=0;
    int num;
    while (1)
    {
        sem_wait(&xfull);
        num = queque[(i++)%_SEM_CNT_];
        printf("i = %d \n",i);
        printf("------%s----self-%lu---num---%d---\n",__FUNCTION__,pthread_self(),num);
        
        sem_post(&blank);
        sleep(rand()%4);
    }
    
    return NULL;
}
int main()
{
    sem_init(&blank ,0,_SEM_CNT_);//初始化为5  最多装5个
    sem_init(&xfull,0,0);//初始化为0 默认没有商品
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,thr_product,NULL);
    pthread_create(&tid[1],NULL,thr_consumer,NULL);

    pthread_join(tid[0],NULL);//回收
    pthread_join(tid[1],NULL);

    sem_destroy(&blank);
    sem_destroy(&xfull);
    return 0;
}