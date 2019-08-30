//设置线程属性
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *thr(void *arrg)
{
    printf("I am a thread\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);//初始化属性
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置属性分离
    pthread_create(&tid,&attr,thr,NULL);//用属性创建线程
    int ret;
    if((ret = pthread_join(tid,NULL))>0)
    {
        printf("joint err:%d,%s\n",ret,strerror(ret));
    }
    pthread_attr_destroy(&attr);//摧毁属性
    return 0;
}