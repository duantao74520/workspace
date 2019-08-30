#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    link("hello","hello1");//硬链接
    symlink("hello","hello2");//软连接
    char buf[256] ={0};
    readlink("hello2",buf,sizeof(buf));//读取软连接
    printf("buf is %s\n",buf);
    unlink("hello1");//删除链接
}