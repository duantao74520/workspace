//epoll 边沿触发 非阻塞
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
int main()
{
    //创建socket 
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    //绑定
    struct sockaddr_in sever_addr,client_addr;
    sever_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sever_addr.sin_port = htons(6666);
    sever_addr.sin_family = AF_INET;
    bind(lfd,(struct sockaddr*)&sever_addr,sizeof(sever_addr));
    //监听
    listen(lfd,256);
    //创建根节点
    int epfd = epoll_create(3000);
    //根节点上树
    struct epoll_event ev;
    ev.data.fd = lfd;
    ev.events = EPOLLIN|EPOLLET;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);

    struct epoll_event events[3000];//用来存储3000个事件
    printf("开始监听\n");

    while (1)
    {
        //委托内核检测时间 IO多路转接技术 
        int ret = epoll_wait(epfd,events,3000,-1);//阻塞监听 有事件则保存在events中

        if(ret == -1 )
        {
            perror("epoll wait");
        }
        //根据ret遍历 events 
        for(int i =0;i<ret;i++)
        {
           
            
            int fd = events[i].data.fd;
            if(fd == lfd)
            {
                //有新的客户端请求连接
                socklen_t client_len = sizeof(client_addr);
                int cfd = accept(lfd,(struct sockaddr *)&client_addr,&client_len);
                char IP[256];
                printf("clent connect IP = %s , port = %d",
                        inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,IP,sizeof(IP)),
                        ntohs(client_addr.sin_port)
                        );
                  
                //设置cfd = 非阻塞
                int flag = fcntl(cfd,F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(cfd,F_SETFL,flag);

                ev.data.fd = cfd;
                //边沿模式 需要在这儿修改
                ev.events = EPOLLIN| EPOLLET;//加上EPOLLET
                //新来的挂数
                epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
            }

            else
            {
                //只处理read命令
                if(! events[i].events & EPOLLIN)
                {
                    continue;
                }

                char buf[5] = {0};
                int len ;
                //循环读数据
                while((len = recv(fd, buf, sizeof(buf) ,0 ))>0) 
                {
                   // printf("len = %d",len);
                    //数据打印到终端
                    write(STDOUT_FILENO,buf,len);
                    //回传
                    send(fd,buf,len,0);

                }
                if(len == 0)
                {
                    printf("-----------------\n");
                    printf("客户端断开了连接\n");
                    int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
                    if(ret == -1 )
                    {
                        perror("epoll ctl error");
                        exit(1);
                    }
                    close(fd);

                }
                else if(len == -1)
                {
                    if(errno == EAGAIN)
                    {
                        printf("缓冲区数据已经读完\n");
                    }
                    else
                    {
                      perror("recv error");
                       exit(1);
                     }
                }

            }
        }
    }
    close(lfd);
    return 0;
    
}