//需求：打开文件，写入内容：helloworld,然后读取一下该文件内容打印到屏幕

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
    int fd = open (argv[1],O_RDWR|O_CREAT,0666);
    write(fd,"helloworld\n",11);
    //文件读写位置此时到了末尾
    //需要移动读写位置
    lseek(fd,0,SEEK_SET);//移动到哪儿
    char buf[256] = {0};
    int ret = read(fd,buf,sizeof(buf));//返回
    if(ret)
    {
        write(STDOUT_FILENO,buf,sizeof(buf));
    }
    close(fd);
    return 0;
}