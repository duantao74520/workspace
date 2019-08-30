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
    int fd = open(argv[1],O_WRONLY|O_CREAT ,0666);
    //2 lseek  拓展文件
    int ret = lseek(fd,1024,SEEK_END); //利用off_set 拓展文件 1024
    //需要至少写一次 否则无法保存
    write(fd,"a",1);//在后面再写一个
    //3 close
    close(fd);
    return 0;
}
