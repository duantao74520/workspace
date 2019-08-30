//tcp通信 client
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc ,char *argv[])
{
    if(argc <2)
    {
        printf("eg :  a.ot\n");
    }
    int port = atoi(argv[1]);//将字符串转换成整形 端口号
    //创建套接字
    int fd = socket(AF_INET,SOCK_STREAM,0);
    //连接服务器
    struct sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);//大小端转换
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);//把字符串ip 转换成网络IP 必须用pton这个函数
    connect(fd,(struct sockaddr*)&serv ,sizeof(serv));
    
    //通信
    while(1)
    {
        printf("请输入要发送的字符串：\n");
        char buf[256] ={0};
        fgets(buf,sizeof(buf),stdin);
        write(fd,buf,strlen(buf));
        //等待接收数据
        printf("fd = %d\n",fd);
        printf("等待接收数据\n");
        int len = read(fd,buf,sizeof(buf));
        if(len == -1)
        {
            perror("read_error");
            exit(1);
        }
        if(len == 0)
        {
            printf("服务器关闭了连接\n");
            break;
        }
        else
        {
            printf("rev_buf = %s\n",buf);
        }
    }
    close(fd);
    return 0;
}