//看看even支持哪些io转接技术
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <event2/event.h>

int main(int argc,char *arggv[])
{
    //创建一个事件处理框架
    struct event_base *base;
    base = event_base_new();
    //打印支持后端 io转接技术
    //返回的类型是 char*[]的数组指针
    const char ** meths = event_get_supported_methods();
    printf("当前支持技术\n");
    for(int i=0; meths[i]!=NULL;++i)
    {
        printf("%s\n",meths[i]);

    }
    printf("当前使用技术\n");
    printf("%s\n",event_base_get_method(base));
    
    pid_t pid = fork();
    if(pid==0)//子进程
    {
        //在子进程中需要重新初始化
        event_reinit(base);
    }

    //添加事件
    //even_new event_free event_add
    //事件循环
    event_base_dispatch(base);//事件循环会循环很久 
    
    //释放even_base
    event_base_free(base);
    return 0;
}