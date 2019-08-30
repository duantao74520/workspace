//udp client
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

int main(int argc,char *argv[])
{
    //创建套接字
    int lfd = socket(AF_INET,SOCK_DGRAM,0);
    if(lfd ==-1)
    {
        perror("error");
        exit(1);

    }
    //绑定
    struct sockaddr_in serv,client_addr;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htonl(6666);
    
    int ret = bind(lfd,(struct sockaddr*)&serv,sizeof(serv));

    //通信
    while(1)
    {
        char buf[256];
        socklen_t client_len = sizeof(client_addr);
        int recvlen = recvfrom(lfd,buf,sizeof(buf),0,(struct sockaddr*)&client_addr,&client_len);
        printf("recv buf = %s",buf);
        char IP[256];
         printf("clent connect IP = %s , port = %d",
            inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,IP,sizeof(IP)),
            ntohs(client_addr.sin_port)
            );
            //返回
        sendto(lfd,buf,recvlen,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
    }
    close(lfd);
    
}