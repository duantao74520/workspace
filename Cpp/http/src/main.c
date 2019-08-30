#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "epoll_server.h"
int main(int argc,const char *argv[])//可以传递绑定的端口 1端口 2文件运行的文件夹
{
    if(argc < 2 )
    {
        printf("eg :1.out port path \n");
    }

    //端口
    int port = atoi(argv[1]);
    if(argc == 3)
    {
    //修改进程的工作目录
        int ret = chdir(argv[2]);
        if(ret == -1)
        {
            perror("chdir error");
            exit(1);
        }
    }
   
    //启动epoll模型
    epoll_run(port);
    return 0;
}