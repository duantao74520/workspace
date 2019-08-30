#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include "epoll_server.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#define MAXSIZE 2000


void epoll_run(int port)
{
    //创建一个epoll数
    int epfd = epoll_create(MAXSIZE);
    if(epfd ==-1)
    {
        perror("epoll_creat_error");   
        exit(1); 
    }
    //添加要监听的节点
    //先添加监听的lfd

    int lfd =  init_listen_fd(port ,epfd);
    //委托内核检测添加到数上的节点
    struct epoll_event all[MAXSIZE];
    while(1)
    {
        int ret= epoll_wait(epfd,all,MAXSIZE,-1);
        if(ret == -1 )
        {
            perror("epoll_wait_error");
            exit(1);

        }
        //遍历发生变化的节点
        for(int i =0;i<ret;i++)
        {
            //只处理读事件
            struct epoll_event *pev = &all[i];
            if(!(pev->events & EPOLLIN))
            {
                //不是读事件
                continue;
            }
            if(pev->data.fd == lfd )
            {
                //接收连接请求
                do_accept(lfd,epfd);
            }
            else
            {
                //读数据
                do_read(pev->data.fd,epfd);

            }
            
        }
    }
}
void do_read(int cfd,int epfd)
{
    //将浏览器发过来的数据 读到buf中 
    char line[1024] = {0};
    //读请求行
    int len = get_line(cfd,line,sizeof(line));
    if(len == 0)
    {
        //如果读完了 就需要断开连接 
        printf("客户端断开了连接 \n");
        //关闭套接字 cfd从epoll上del
        disconnect(cfd,epfd);
    }
    else if(len == -1)
    {
        perror("客户端断开了连接 \n");
        //关闭套接字 cfd从epoll上del
        disconnect(cfd,epfd);
    }
    else
    {
        printf("请求数据：%s",line);
        printf("================请求头===============\n");
        //还有数据没有读完
        //继续读
        while(len)
        {
            char buf[1024] = {0};
            len = get_line(cfd,buf,sizeof(buf));
            printf("--------:%s",buf);

        }
        printf("===============The End============\n");

    }
    //请求行：get /xxx http/1.1
    //判断是不是get请求 
    if(strncasecmp("get",line,3)==0)//n case忽略大小写
    {
       // printf("=======请求是GET=========\n");
        //处理http请求 拆分请求行
        http_request(line,cfd);
        //关闭套接字 cfd从epoll上del
        disconnect(cfd,epfd);
    }

}
//编码
void encode_str(char *to,int tosize,const char *from)
{
    int tolen;
    for(tolen = 0;*from != '\0' && tolen+4 <tosize;++from)
    {
        if(isalnum(*from) || strchr("/_.-~",*from)!=(char *)0)
        {
            *to = *from;
            ++to;
            ++tolen;
        }
        else
        {
            sprintf(to,"%%%02x",(int)*from &0xff);
            to +=3;
            tolen +=3;
        }
       
    }
    *to = '\0'; 
}
//解码
void decode_str(char *to,char *from)
{
    for(;*from !='\0';++to,++from)
    {
        if(from[0] == '%' && isxdigit(from[1] )&& isxdigit(from[2]))
        {
            *to = hexit(from[1]*16 + hexit(from[2]));
             from +=2;
        }
      
        else
        {
            *to = *from;
        }
    }
    *to = '\0';
    
}
//16进制转10进制
int  hexit(char c)
{
    if(c>='0'&&c<='9')
    {
        return c-'0';
    }
     if(c>='a'&&c<='f')
    {
        return c-'a' +10;
    }
     if(c>='A'&&c<='F')
    {
        return c-'A'+10;
    }
}
//http请求处理
void http_request(const char* request,int cfd)
{
    //拆分请求行
    char method[12],path[1024],protocol[12];
    sscanf(request,"%[^ ] %[^ ] %[^ ]",method,path,protocol); //正则表达式
    printf("method = %s, path = %s ,protocol = %s \n",method,path,protocol);
    //转码 将不能识别的中文乱码 -》
    //解码 %23 %34 %5f
    decode_str(path,path);
    //处理path /xx
    //去掉path中的/
    char *file = path +1;//第一个是/
    //如果没有指定访问的资源 默认显示资源目录中的路径
    if(strcmp(path,"/") == 0)
    {
        //file的值，资源目录的当前位置
        file = "./";
        
    }
    //判断目录还是文件
    //需要获取文件属性
    struct  stat st;
    int ret = stat(file,&st);
    if(ret == -1)
    {
        //show404
        send_respond_head(cfd,404,"File Not Found",".html",-1);
        send_file(cfd,"404.html");
    }
    if(S_ISDIR(st.st_mode))//是目录
    {
        //如果是目录 发送相应目录的东西 
        send_respond_head(cfd,200,"OK",get_file_type(".html"),-1);
        send_dir(cfd,file);

        
    }
    else if(S_ISREG(st.st_mode))//是文件
    {
        //发送消息头
        send_respond_head(cfd,200,"OK",get_file_type(file),st.st_size);
        //发送文件内容
        send_file(cfd,file);
    }


}
//发送目录
void send_dir(int cfd,const char* dirname)
{
    //拼出一个HTML的页面<table></table>
    char buf[4096] = {0};
    sprintf(buf,"<html><head><title>目录名：%s</title></head>",dirname);
    sprintf(buf+strlen(buf),"<body><h1>当前目录：%s</h1><table>",dirname);
    char path[1024] ={0};
    char enstr[1024] = {0};
    //用scandir 便利dir中的文件
    //目录项二级指针
    struct dirent ** ptr;
    int num = scandir(dirname,&ptr,NULL,alphasort);//返回有多少个子文件
    //遍历 
    for(int i = 0;i<num;i++)
    {
        char *name = ptr[i]->d_name;
        //拼接文件的完整路劲 用来判断是文件还是路劲
        sprintf(path,"%s/%s",dirname,name);
        printf("path = %s======== \n",path);
        struct stat st;
        stat(path,&st);

        encode_str(enstr,sizeof(enstr),name);
        //如果是文件
        if(S_ISREG(st.st_mode))
        {
            sprintf(buf +strlen(buf),
                "<tr><td><a href = \"%s\">%s</a><td>%ld</td></tr>",
                enstr,name,(long)st.st_size);
                printf("文件名：%s\n",buf);
        }
        //如果是目录
        if(S_ISDIR(st.st_mode))
        {
            sprintf(buf +strlen(buf),
                "<tr><td><a href = \"%s/\">%s/</a></td><td>%ld</td></tr>",
                enstr,name,(long)st.st_size);
        }

        send(cfd,buf,strlen(buf),0);
        memset(buf,0,sizeof(buf));

        //字符串拼接
    }
    sprintf(buf+strlen(buf),"</table></body></html>");
    send(cfd,buf,sizeof(buf),0);
    printf("dir message send ok!!\n");


#if 0
    //打开目录
    DIR *dir = opendir(dirname);
    if(dir == NULL)
    {
        perror("opendir error");
        exit(1);
    }
    //读目录
    struct dirent *ptr = NULL;
    while((ptr = readdir(dir))!=NULL)
    {
        sprintf(buf,"<tr><td></td>")
        char *name = ptr->d_name;
    }
    closedir(dir);
#endif
    
}
//发送相应头
void send_respond_head(int cfd,int no,const char * desp,const char *type,long len)
{
    char buf[1024] ={0};
    //状态行
    sprintf(buf,"http/1.1 %d %s\r\n",no,desp);
    send(cfd,buf,strlen(buf),0);
    //消息报头
    sprintf(buf,"Content-Type:%s\r\n",type);
    sprintf(buf+strlen(buf),"Content-Length:%ld\r\n",len);
    send(cfd,buf,strlen(buf),0);
    //空行
    send(cfd,"\r\n",2,0);
}
//发送相应文件
void send_file(int cfd,const char *filename)
{
    //打开文件
    int fd = open(filename,O_RDONLY);
    if(fd == -1)
    {
        //show 404
        return;
    }
    //循环读
    char buf[4096] = {0};
    int len = 0;
    while((len = read(fd,buf,sizeof(buf)))>0)
    {
        //发送读出来的数据
        send(cfd,buf,len,0);
    }
    if(len == -1)
    {
        perror("read file error");
        exit(1);
    }
    close(fd);
}
//断开连接
void disconnect(int cfd,int epfd)
{
    int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,cfd,NULL);
    if(ret == -1)
    {
        perror("disconnect error");
        exit(1);
    }
    printf("============cfd:%d：断开连接=====\n",cfd);
    close(cfd);
}


int get_line(int sock,char *buf,int size)
{
    int i = 0;
    char c = '\0';
    int n;
    while ((i < size - 1)&& (c != '\n'))
    {
       n = recv(sock,&c,1,0);//这儿必须是非阻塞的 才能返回0 
       if(n>0)
       {
            if(c == '\r')//在这儿读下一个是否为 \n 
            {
                n = recv(sock,&c,1,MSG_PEEK);//每次试探性的读一个数据 不取出
                if((n>0) && (c =='\n'))
                {
                    recv(sock,&c,1,0);
                }
                 else
                {
                    c = '\n';
                }
            }
           
            buf[i] = c;
            i++;
       }
       else
       {
           c = '\n';
       }
      
    }
    buf[i] = '\0';
    return i;
    

}
//接收新的连接请求
void do_accept(int lfd,int epfd)
{
    struct sockaddr_in clientl;
    socklen_t len = sizeof(clientl);
    int cfd = accept(lfd,(struct sockaddr*)&clientl ,&len);
    if(cfd == -1)
    {
        perror("cfd error");
        exit(1);
    }
    //打印客户端信息
    char ip[256] = {0};
    printf("New Client IP :%s ,Port %d, cfd = %d \n",
            inet_ntop(AF_INET,&clientl.sin_addr.s_addr,ip,sizeof(ip)),
            ntohs(clientl.sin_port),cfd);
    //设置cfd为非阻塞
    int flag = fcntl(cfd,F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(cfd,F_SETFL,flag);
    //将节点挂到epoll树上
    struct  epoll_event ev;
    ev.data.fd = cfd;
    //边沿非阻塞
    ev.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
    if(ret == -1)
    {
        perror("epoll ctl add_cfd error");
        exit(1);
    }
}

int init_listen_fd(int port ,int epfd)
{
    //创建监听的套接字；
    int lfd = socket(AF_INET,SOCK_STREAM,0);

    //绑定
    struct  sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    

    //端口复用
    int flag =1 ;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));//设置端口复用
    int ret = bind(lfd,(struct sockaddr *)&serv,sizeof(serv));//再绑定
    if(ret == -1)
    {
        perror("bind error");
        exit(1);
    }
    //监听
    ret =  listen(lfd,64);
    if(ret == -1)
    {
        perror("listen  error");
        exit(1);
    }
    //lfd,添加到epoll树上
    struct epoll_event ev;
    ev.data.fd = lfd ;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);
    if(ret == -1)
    {
        perror("epoll_ctl add lfd error");
        exit(1);
    }

    return lfd;
}

// 通过文件名获取文件的类型
const char *get_file_type(const char *name)
{
    char* dot;

    // 自右向左查找‘.’字符, 如不存在返回NULL
    dot = strrchr(name, '.');   
    if (dot == NULL)
        return "text/plain; charset=utf-8";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp( dot, ".wav" ) == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";
}