//epoll 水平触发函数
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <ctype.h>
#include <sys/epoll.h>
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
    ev.events = EPOLLIN;
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
                
                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
            }

            else
            {
                //只处理read命令
                if(! events[i].events & EPOLLIN)
                {
                    continue;
                }

                char buf[5];
                int len = read(fd,buf,sizeof(buf));//每次只读五个字节 

                if(len == -1)
                {
                    perror("read error");
                }
                if(len == 0)
                {
                    close(fd);
                    printf("client %d close\n",fd);
                    epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
                }

                else
                {
                   // printf("  rev buf =%s \n",buf); //缓冲区默认大小8k 
                    //printf("打印结束\n");
                    write(STDOUT_FILENO,buf,len);
                    write(fd,buf,len);
                }

            }
        }
    }
    return 0;
    
}