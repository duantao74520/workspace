//用libevent 实现 套接字通信
//相当于封装了epoll可以处理高并发的web服务器

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <arpa/inet.h>
//读回调
void  read_cb(struct bufferevent *bev, void *ctx)
{
    char buf[1024] = {0};
    int len = bufferevent_read(bev,buf,sizeof(buf));
    printf("recv : %s\n",buf);
    //给对方发送数据
    //bufferevent_write(bev,buf,sizeof(buf));
    
}
//写回调
void write_cb(struct bufferevent *bev, void *ctx)
{
    printf("发送回调\n");
}
//事件回调
void event_cb(struct bufferevent *bev, short what, void *ctx)
{
    if(what & BEV_EVENT_EOF)
        printf("connect close");
    else if (what & BEV_EVENT_ERROR)
        printf("fome other error\n");

    //释放资源
    bufferevent_free(bev);
    printf("bev资源已经被释放");
}

//读写到终端的数据 这时候只要键盘有输入 就可以检测到
void  send_cb(evutil_socket_t fd, short what, void * arg)
{
    //给发送的socket event发送数据
    //因为这个回调函数没有bufferevent
    printf("键盘收到数据\n");
    struct bufferevent * bev = (struct bufferevent *) arg;
    char buf[1024] = {0};
    int len = read(fd,buf,sizeof(buf));
    //将终端
    bufferevent_write(bev,buf,len+1);
}



int main(int argc, const char *argv[])
{
    //创建事件处理框架
    struct event_base * base = event_base_new();
  
    //创建事件
    int fd = socket(AF_INET,SOCK_STREAM,0);
    struct bufferevent *bev =  bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
    //给缓冲区设置回调
    bufferevent_setcb(bev,read_cb,write_cb,event_cb,NULL);
    //连接服务器
    struct sockaddr_in cli;
    cli.sin_family = AF_INET;
    cli.sin_port = htons(5678);
    inet_pton(AF_INET,"127.0.0.1",&cli.sin_addr.s_addr);
    bufferevent_socket_connect(bev,(struct sockaddr*)&cli,sizeof(cli));
    bufferevent_enable(bev,EV_READ);

    //接收键盘输入事件
    //创建一个新的事件
    struct event * ev = event_new(base,STDIN_FILENO,EV_READ|EV_PERSIST,send_cb,bev);
    event_add(ev,NULL);
    //连接服务器
    //开始事件循环
    event_base_dispatch(base);
    //释放资源
    bufferevent_free(bev);

    event_base_free(base);
    return 0;
}