//高并发服务器 多线程版本
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>

#define MAXLINE 80
#define SER_PORT 6666
typedef struct t_sock
{
    struct sockaddr_in client_addr;
    int cfd;
} t_sock_t;
void *doWork(void *arg)
{
    t_sock_t* client = (t_sock_t *)arg;
    pthread_detach(pthread_self());//线程分离
    char IP[256];
    char buf[256];
    printf("client IP =%s ,port = %d",
            inet_ntop(AF_INET,&client->client_addr.sin_addr.s_addr,IP,sizeof(IP)),
            ntohs(client->client_addr.sin_port));
    while(1){
        int len = read(client->cfd,buf,sizeof(buf));
        if(len == -1)
        {
            perror("read error");
            pthread_exit(NULL);
        }
        if(len ==  0)
        {
            perror("客户端断开连接");
            close(client->cfd);
            break;
        }
        else
        {
            printf("rev buf = %s\n",buf);
            write(client->cfd,buf,len);

        }
    }
    return 0;
}
int main()
{

    //创建套接字
    int lfd =  socket(AF_INET,SOCK_STREAM,0);
    //绑定 ip 和端口
    struct sockaddr_in serv;
    serv.sin_port = htons(SER_PORT);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);//本地ip
    bind(lfd,(struct sockaddr *)&serv,sizeof(serv));
    //监听
    listen(lfd,256);//最多同时连接256个
    //等待并接收连接请求
    //需要有一个传出参数保存地址和port
    struct sockaddr_in clien_addr;
    socklen_t clien_len = sizeof(clien_addr);
    t_sock_t client[256];//256个客户端 用来开线程
    int index;
    for (size_t i = 0; i < sizeof(client)/sizeof(client[0]); i++)
    {
        client[i].cfd = -1;
    }
    
    pthread_t tid;
    printf("开始监听\n");
    while (1)
    {
        for(index =0;index <256;index++)
        {
            if(client[index].cfd ==-1)
            {
                break;
            }
        }
        if(index == 256)
        {
            break;
        }
        int cfd = accept(lfd,(struct sockaddr *)&clien_addr,&clien_len);
        client[index].cfd = cfd;
        client[index].client_addr = clien_addr;
        pthread_create(&tid,NULL,doWork,(void *)&client[index]);
        index ++;
        
    }
    return 0;
}