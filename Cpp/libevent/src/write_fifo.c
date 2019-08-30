//写管道操作
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <event2/event.h>
#include <time.h>

//对事件的回调函数
void write_cb(evutil_socket_t fd,short what,void *arg)//回调函数的格式必须是这样的
{
    //写管道
    char buf[1024] = {0};
    static num = 0 ;
    sprintf(buf,"hello world == %d\n",num++);
    write(fd,buf,strlen(buf));


}
//写管道
int main(int argc,const char *argv[])
{


    //open file
    int fd = open("myfifo",O_WRONLY|O_NONBLOCK);//非阻塞
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }
    //读管道
    struct event_base * base =NULL;//创建event事件框架
    base = event_base_new();

    //创建事件
    struct event * ev = NULL;
    ev = event_new(base,fd,EV_WRITE,write_cb,NULL);//检测的是写缓冲区是否可以写 fifo默认大小4k

    //添加事件
    event_add(ev,NULL);//阻塞等待事件发生 timeout = NULL

    //事件循环
    event_base_dispatch(base);

    //释放资源
    event_free(ev);
    event_base_free(base);
    close(fd);

    return 0;
}