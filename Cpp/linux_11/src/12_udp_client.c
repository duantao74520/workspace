//udp  client
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
    //创建套接字
    int lfd = socket(AF_INET,SOCK_DGRAM,0);
    //初始化服务器的ip 和 端口
    struct sockaddr_in serv;
    serv.sin_family =AF_INET;
    serv.sin_port = htons(6666);
    inet_pton(AF_INET, "127.0.0.1" ,&serv.sin_addr.s_addr);
    //通信
    while(1)
    {
        //发送数据
        char buf[256];
        fgets(buf,sizeof(buf),stdin);
        printf("已经发送\n");
        sendto(lfd,buf,strlen(buf)+1,0,(struct sockaddr*)&serv,sizeof(serv));
        //等待服务器数据
        recvfrom(lfd,buf,sizeof(buf),0,NULL,NULL);
    }
    close(lfd);
    return 0;
}