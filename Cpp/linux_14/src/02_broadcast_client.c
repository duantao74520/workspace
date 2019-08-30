//广播 client
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

int main()
{
    //socket
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd == -1)
    {
        perror ("sock error");
        exit(1);
    }
    //绑定IP 端口
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(6767);
    inet_pton(AF_INET,"0.0.0.0",&client.sin_addr.s_addr);
    //绑定
    int ret =  bind(fd,(struct sockaddr*)&client,sizeof(client));
    while(1)
    {
        //接收数据
        char buf[1024] = {0};
        int len = recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);
        if(len ==  -1)
        {
            perror("client error");
            exit(1);
        }
        printf("client == recv buf :%s\n",buf);

    }
}