//本地套接字 server
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
    int lfd = socket(AF_LOCAL,SOCK_STREAM,0);
 //  如果存在 删除套接字文件
    unlink("server.sock");
    //绑定
    struct sockaddr_un serv;
    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path,"server.sock");
    int ret =  bind(lfd,(struct sockaddr*)&serv,sizeof(serv));
   
    //监听
    listen(lfd,36);

    //等待连接请求
     struct sockaddr_un client;
     socklen_t len = sizeof(client);
    int cfd = accept(lfd,(struct sockaddr *)&client,&len);
    
    while(1)
    {
        char buf[256] = {0};
        int recvlen = recv(cfd,buf,sizeof(buf),0);
        if(recvlen == 0)
        {
            printf("client ddisconnect ...\n");
            close(cfd);
            break;

        }
        else
        {
            printf("clien recv %s\n",buf);
            send(cfd,buf,recvlen,0);
        }
    }
    close(lfd);
    return 0;
}