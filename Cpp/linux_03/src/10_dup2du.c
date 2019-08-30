#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
int main()
{
    //先备份现场
    int outfd = dup(1);
    printf("%d\n",outfd);
    //先做重定向
    int fd = open("hello_word",O_WRONLY|O_CREAT,0777);
    dup2(fd,1);//将标准输出重定向到fd对应的文件
    //需要刷新一下 
    fflush(stdout);
    printf("hello2 world\n");
 
    
    //需要恢复1 重新对应标准输出
    dup2(outfd,1);
    printf("hello world2\n");
    close(fd);
    return 0;
    
    }