//tcp通信 server
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
#define MAXLINE 80
#define SER_PORT 6666
int main(void)
{
    //创建套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    //绑定端口
    struct sockaddr_in serv,clientaddr;
    serv.sin_port = htons(SER_PORT);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);//代表本地ip
    bind(listenfd,(struct sockaddr *)&serv,sizeof(serv));//需要类型转换 才能使用sockaddr
    //监听
    listen(listenfd,20);//最多20个用户
    //接收并连接
    printf("正在监听:\n");

    while(1)
    {
        socklen_t client_len = sizeof(clientaddr);
        int cfd =  accept(listenfd,(struct sockaddr *)&clientaddr,&client_len);//传出参数 cfd是文件描述符 clientaddr是传出的客户端 client_len 长度
        char buf[256] = {0};
        char str[MAXLINE];
        int n = read(cfd,buf,sizeof(buf));//阻塞读 返回读到多少数
        printf("receive from %s at port %d \n",inet_ntop(AF_INET,&clientaddr.sin_addr,str,sizeof(str)),ntohs(clientaddr.sin_port));
        for (size_t i = 0; i < n; i++)
        {
            buf[i] = toupper(buf[i]);
            write(cfd,buf,n);
            printf("收到：%s\n",buf);
            close(cfd);
        }
        return 0;
        
    }

    return 0;
}