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

//读回调
void  read_cb(struct bufferevent *bev, void *ctx)
{
    //读bufferevent读缓冲区的数据
    //用bufferevent_read()读
    char buf[1024] = {0};
    bufferevent_read(bev,buf,sizeof(buf));
    printf("recive buf :%s\n",buf);

    //发送数据 往缓冲区写数据
    char sendbuf[1024] = "你发的数据我们已经收到了\n";
    bufferevent_write(bev,sendbuf,strlen(sendbuf)+1);
    printf("我发送了数据,给客户端.....\n");

}
//写回调
void write_cb(struct bufferevent *bev, void *ctx)
{
    printf("发送回调\n");
}
//事件回调
void even_cb(struct bufferevent *bev, short what, void *ctx)
{
    if(what & BEV_EVENT_EOF)
        printf("connect close");
    else if (what & BEV_EVENT_ERROR)
        printf("fome other error\n");

    //释放资源
    bufferevent_free(bev);
    printf("bev资源已经被释放");
}

//连接完成之后，对应的通信操作
void listen_cb(struct evconnlistener * listener, evutil_socket_t fd, struct sockaddr * addr, int socklen, void * ptr)//代表有新的连接的时候会调用回调函数
{
    printf("收到请求连接\n");
    //因为没有base 所以必须在ptr转成base的类型
    struct event_base * base = (struct event_base *) ptr;
    //套接字通信 用带缓冲区的socket——buffer带缓冲区的事件
    //先接收数据 然后发送数据
    struct bufferevent * bev = NULL;
    bev = bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);//关闭之后需要自动回收fd
    //给bufferevent的缓冲区设置回调函数
    bufferevent_setcb(bev,read_cb,write_cb,even_cb,NULL);
    //设置读缓冲区的回调可用 ，默认写是可用的
    bufferevent_enable(bev,EV_READ);

}


int main(int argc, const char *argv[])
{
    //创建事件处理框架
    struct event_base * base = event_base_new();
    //server info
    struct sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5678);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);//本地ip

    //创建监听套接字 这儿是创建的监听套接字 相当于说是 ip+端口为一个fd
    struct evconnlistener * listen = NULL;
    //创建套接字 并接收连接请求  当有新连接的时候 listen_cb 被调用了
    listen = evconnlistener_new_bind( base,listen_cb,base,
                                    LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
                                    -1,(struct sockaddr *)&serv, sizeof(serv));//框架，回调函数，参数,flag,backlog,

    //开始事件循环
    event_base_dispatch(base);
    //释放资源
    evconnlistener_free(listen);
    event_base_free(base);
    return 0;
}