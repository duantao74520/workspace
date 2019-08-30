//用条件变量实现生产者消费者的模型
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond =PTHREAD_COND_INITIALIZER;

int begingnum = 1000;
typedef struct _ProdInfo{
    int num;
    struct _ProdTnfo *next;

} ProdInfo;
ProdInfo *HEAD =NULL;
void *thr_productor(void *arg)
{
    //负责在链表添加数据
    while(1)
    {
        ProdInfo * prod = malloc(sizeof(ProdInfo));
        prod->num = begingnum++;
        pthread_mutex_lock(&mutex);//加锁
        //add to list
        prod->next = HEAD;//插头
        HEAD = prod;
        pthread_mutex_unlock(&mutex);//解锁
        printf("product---\n");
        //发起通知
        pthread_cond_signal(&cond);//数据已经进去 通知消费者
        sleep(rand()%4);
    }
}
void *thr_customer(void *arg)
{
    ProdInfo  *prod = NULL;
    //取链表数据
    while(1)
    {
        pthread_mutex_lock(&mutex);
        //if(HEAD == NULL)
        while(HEAD ==NULL)
        {
            //等待条件量 如果没有则并释放mutex
            //阻塞在这儿 等待条件量的信号
            //在此之前必须要加锁
            pthread_cond_wait(&cond,&mutex);
        }
        prod = HEAD;
        HEAD = HEAD->next;
        printf("------%d------%lu\n",prod->num,pthread_self());
        pthread_mutex_unlock(&mutex);
        free(prod);
        sleep(rand()%2);
    }
    return NULL;
}
int main()
{
    pthread_t tid[5];
    for (size_t i = 0; i < 4; i++)
    {
       pthread_create(&tid[i],NULL,thr_customer,NULL);
    }
    
    
    pthread_create(&tid[4],NULL,thr_productor,NULL);
    for (size_t i = 0; i < 5; i++)
    {
        pthread_join(tid[i],NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}