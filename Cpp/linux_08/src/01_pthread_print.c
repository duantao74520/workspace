//上锁 打印两个helloworld
//注意有两种控制方式

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//常量初始化

void *thr1(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);//加锁
        printf("hello");
        sleep(rand()%3);
        printf("world\n");
        pthread_mutex_unlock(&mutex);//解锁
        sleep(rand()%3);
    }
    return NULL;
    
}
void *thr2(void *arg)
{
   while (1)
   {
        pthread_mutex_lock(&mutex);//加锁
        printf("HELLO");
        sleep(rand()%3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);//解锁
        sleep(rand()%3);

   }
   return NULL;
   
}

int main()
{
    srand(time(NULL));
    pthread_t tid1,tid2 ;
    pthread_attr_t attr;
    //pthread_mutex_init(&mutex,NULL);//锁初始化
    pthread_attr_init(&attr);//参数初始化
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_create(&tid1,&attr,thr1,NULL);
    pthread_create(&tid2,&attr,thr2,NULL);

    pthread_mutex_destroy(&mutex);//摧毁锁
    while(1);
    return 0;

}