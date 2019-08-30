//实现Cat

#include <sys/types.h>
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
    int fd = open(argv[1],O_RDONLY);

    //读 输出到屏幕
    char buf[250];
    int ret = read(fd,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,ret);//写到屏幕
    //循环读取 读到\0结束
    close(fd);
    return 0;

}
