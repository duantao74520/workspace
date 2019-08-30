//本地套接字
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
#include <sys/un.h>

int main()
{
    int fd = socket(AF_LOCAL,SOCK_STREAM,0);
 //  如果存在 删除套接字文件
    unlink("client.sock");
    //--------
    //给客户端绑定一个套接字文件
    struct sockaddr_un client;
    client.sun_family = AF_LOCAL;
    strcpy(client.sun_path,"client.sock");
    int ret = bind(fd,(struct sockaddr*)&client,sizeof(client));

    //连接 需要server端的信息
    struct sockaddr_un serv;
    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path,"server.sock");
    //连接服务器
    connect(fd,(struct sockaddr*)&serv,sizeof(serv));

    //通信你
    while (1)
    {
        /* code */
        char buf[1024] = {0};
        fgets(buf,sizeof(buf),stdin);
        send(fd,buf,sizeof(buf),0);

        recv(fd,buf,sizeof(buf),0);

       printf("clien recv %s\n",buf);
    }
    close(fd);

}