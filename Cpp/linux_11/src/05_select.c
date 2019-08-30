//利用IO多路转接技术，利用一个进程搞定多个客户端的连接
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
#include <sys/time.h>
#define MAXLINE 80
#define SER_PORT 6666


int main()
{
    //创建套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    //绑定端口
    struct sockaddr_in serv;
    serv.sin_port = htons(SER_PORT);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);//代表本地ip
    bind(listenfd,(struct sockaddr *)&serv,sizeof(serv));//需要类型转换 才能使用sockaddr
    //监听
    listen(listenfd,20);//最多20个用户
    //接收并连接
    printf("正在监听:\n");
    struct sockaddr_in clientaddr;
    socklen_t client_len = sizeof(clientaddr);

    //创建一个文件描述符表
    fd_set reads,temp;//temp用来临时保存传入参数
    //初始化
    FD_ZERO(&reads);//清零
    //监听的lfd加入到读集合
    FD_SET(listenfd,&reads);//用以检测有没有客户端请求连接
    //如果有新连接 相应的内核缓冲区的read端有数据 
    int maxfd = listenfd;

    while(1)
    {
        //委托检测新的连接
        temp =reads;
        int ret = select(maxfd+1,&temp,NULL,NULL,NULL);//永久阻塞
        if(ret == -1)
        {
            perror("select error");
            exit(1);
        }
        //判断是不是监听的 及有新的客户端连接
        if(FD_ISSET(listenfd,&temp))
        {
            //如果条件成立说明有新的连接 接收连接请求
            int cfd = accept(listenfd,(struct sockaddr *)&clientaddr,&client_len);
            char ip[64];
           printf("new client ip = %s ,port = %d",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(clientaddr.sin_port));
            //cfd加入读集合  下一次就可以检测到了
            FD_SET(cfd,&reads);
            //最大的文件描述符也会变化 所以需要更新maxfd
            maxfd = maxfd <cfd ? cfd:maxfd;
        }
        //客户端发送数据 服务器检测
        for(int i = listenfd + 1;i<=maxfd;i++)
        {
            if(FD_ISSET(i,&temp))
            {
                char  buf[256];
                int len = read(i,buf,sizeof(buf));
                if(len == -1)
                {
                    perror("read error");
                    exit(-1);
                }
                if(len == 0)
                {
                    printf("客户端已经断开连接\n");
                    //cfd从读集合中删除 因为没有数据了
                    FD_CLR(i,&reads);
                }
                else
                {
                    printf("rev buf =%s\n",buf);
                    write(i,buf,len);    
                }
                

            }
        }
    }
}