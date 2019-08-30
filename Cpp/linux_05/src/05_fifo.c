//fifo 写
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char *argv[])
{
    if(argc !=2)
    {
        printf("a.out\n");
        return -1;
    }
    //当前有个fifo myfifo文件
    //打开fifo文件
    int fd = open(argv[1],O_WRONLY);
    //写
    char buf[256];
    int num =1;
    while(1){
        memset(buf,0x00,sizeof(buf));
        //循环写
        sprintf(buf,"xiaoming%04d\n",num++);
        write(fd,buf,strlen(buf));
        sleep(1);
    }
    close(fd);//关闭
    return 0;
}