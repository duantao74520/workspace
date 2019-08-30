#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    close(1);
    int fd = open("1.log",O_CREAT|O_TRUNC|O_WRONLY,0644);//分别为文件名 参数 权限掩码
    //open 返回当前最小可用的文件描述符 如果不关闭的话 就是3 如果关闭的话就是1
    // fd 是一个数字 代表 0123
    printf("hello owrld\n");
    fflush(stdout);//刷新缓冲区
    close(fd);
    return 0;

}