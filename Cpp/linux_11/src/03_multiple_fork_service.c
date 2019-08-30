//高并发 多进程版本
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
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define MAXLINE 80
#define SER_PORT 6666
void catchSig(int num)
{
    pid_t wpid ;
    while((wpid = waitpid(-1,NULL,WNOHANG))>0)
    {
        sleep(1);
        if(wpid >0 )
        {
            printf("wait child %d ok \n",wpid);
        }
    }
}
int main(void)
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
    //创建信号回收子进程pcb
    struct sigaction act;//注册捕捉函数
    act.sa_flags = 0;
    act.sa_handler = catchSig;
    __sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD,&act,NULL);

    while(1)
    {
        // accept 阻塞的时候被信号中断，处理信号对应的操作以后
        //回来以后就不阻塞了，直接返回-1，这时候 errno == EINTR
        //一定要注意
        int cfd =  accept(listenfd,(struct sockaddr *)&clientaddr,&client_len);//传出参数 cfd是文件描述符 clientaddr是传出的客户端 client_len 长度
        if(cfd == -1 && errno == EINTR)
        {
            cfd =  accept(listenfd,(struct sockaddr *)&clientaddr,&client_len);
        }
        printf("connect sucessful \n");
        int pid = fork();//创建新的进程
        
        if(pid == 0 )//子进程
        {
            close(listenfd);
            char buf[1024] = {0};
            while(1)
            {
                char ip[64];
                printf("client IP: %s port :%d",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(clientaddr.sin_port));
                int len = read(cfd,buf,sizeof(buf));
                if(len == -1)
                {
                    perror("read error");
                    exit(1);
                    break;
                }
                else if(len == 0)
                {
                    perror("客户端断开连接");
                    close(cfd);
                    break;
                }
                else
                {
                    printf("rev buf :%s\n",buf);
                    write(cfd,buf,len);
                }
            }
            return 0;//进程结束
            
        }
        else if(pid >0)//父进程
        {
            close(cfd);
        }
        
    }

    return 0;
}