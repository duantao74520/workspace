//哲学家用餐模型
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define __PHILO_CNT_ 5 //哲学家人数
pthread_mutex_t mutex[__PHILO_CNT_];//5个互斥量

void *thr(void *arg)
{
    srand(time(NULL));
    int num = (int)arg;
    printf("--%d--create--\n",num);
    int left,right;
    if(num == (__PHILO_CNT_-1))
    {
        left = 0,right = num;
    }
    else
    {
        left = num,right = num+1;
    }
    while(1)
    {
        pthread_mutex_lock(&mutex[left]);//加左锁
        //printf("--%d--get left lock--\n",num);
        int ret;
        if((ret = pthread_mutex_trylock(&mutex[right])) ==0)//加右锁
        {
            printf("--%d---eat--noodle--\n",num);
            pthread_mutex_unlock(&mutex[right]);
        }
        
        pthread_mutex_unlock(&mutex[left]);
        sleep(rand()%3);
    }
    return NULL;
}

int main()
{
    pthread_t tid[__PHILO_CNT_];//线程个数
    for (size_t i = 0; i < __PHILO_CNT_; i++)
    {
         pthread_mutex_init(&mutex[i],NULL);//互斥量
    }
    
    for (size_t i = 0; i < __PHILO_CNT_; i++)
    {
        pthread_create(&tid[i],NULL,thr,(void*)i);//创建线程
       
    }

    for (size_t i = 0; i < __PHILO_CNT_; i++)//回收 和销毁
    {
        pthread_join(tid[i],NULL);
        pthread_mutex_destroy(&mutex[i]);
    }
    
    return 0;
    
}