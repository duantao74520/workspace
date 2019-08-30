//需求：计算文件大小

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
    if(argc !=2 )
        {
            printf("./a.out filename \n");
            return -1;
        }
    //01打开文件
    int fd = open(argv[1],O_RDONLY);
    //2 lseek 得到返回值
    int ret = lseek(fd,0,SEEK_END);
    printf("file size is: %d\n",ret);
    //3 close
    close(fd);
    return 0;
}
