//mmap 共享存储映射
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
int main()
{
    int fd = open("mem.txt",O_RDONLY);
   // int fd = open("mem1.txt",O_RDWR|O_CREAT|O_TRUNC,0664);
   // ftruncate(fd,100);//文件100大小
    //共享存储映射
    char *mem = (char *)mmap(NULL,100,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mem == MAP_FAILED)
    {
        perror("mmap error");
        return -1;
    }
    //拷贝数据
    strcpy(mem,"world");//相当于就是对文件操作，速度快
    //释放mmap
    munmap(mem,100);
    return 0;
}