//广播 server

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

    //绑定server的ip和端口
    struct sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(6666);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("inaddr_any %s",INADDR_ANY);
    int ret = bind(fd,(struct sockaddr *)&serv,sizeof(serv));
    //初始化客户端的地址信息
    struct sockaddr_in client;
    client.sin_family =AF_INET;
    client.sin_port =  htonl(6767);//客户端要绑定的端口
    //使用广播地址给客户端发数据
    inet_pton(AF_INET,"172.0.0.255",&client.sin_addr.s_addr);
    //给服务器开放广播权限
    int flag;
    setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));


    //通信
    while(1)
    {

        //一直发数据
        static int num = 0;
        char buf[1024] = {0};
        sprintf(buf,"hello ,udp == %d\n",num++);
        int ret = sendto(fd,buf,strlen(buf)+1,0,(struct sockaddr *)&client,sizeof(client));
        if(ret == -1)
        {
            perror("sent error");
        }
        printf("send buf = %s \n",buf);
        sleep(1);
    }
    close(fd);
    return 0;

}