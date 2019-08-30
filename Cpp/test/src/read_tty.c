#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
    int fd = open("/dev/tty",O_RDWR);
    //int fd = open("/dev/tty",O_RDWR|O_NONBLOCK);//利用非堵塞模式
    
    //fcnt1()函数，设置非阻塞
    int flags = fcntl(fd,F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(fd,F_SETFL,flags);


    char buf[256];
    int ret =0;
    while(1)
    {
        ret = read(fd,buf,sizeof(buf));
        if(ret < 0 ){
            perror("read error\n");
        }
        if(ret)
        {
            printf("rev buf is : %s\n",buf);
        }
        sleep(1);
        printf("end\n");
    }
    close(fd);
    return 0;
}