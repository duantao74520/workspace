#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{

    //先切换工作目录
    chdir("bbb");
    //显示当前目录
    char buf[256] ={0};
    getcwd(buf,sizeof(buf));
    int fd = open("hello",O_WRONLY|O_CREAT,0666);
    write(fd,buf,sizeof(buf));
    close(fd);
    printf("buf is %s\n",buf);
    return 0;
}