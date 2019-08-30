//fifo 读
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
    int fd = open(argv[1],O_RDONLY);
    //写
    char buf[256];
    int ret;
    while(1){
        ret = read(fd,buf,sizeof(buf));
        if(ret > 0 )
        {
            printf("read : %s\n",buf);
        }
        sleep(1);
    }
    close(fd);//关闭
    return 0;
}