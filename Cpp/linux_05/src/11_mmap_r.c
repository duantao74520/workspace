//mmap 无血缘的进程通信 读
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
typedef struct _Student
{
    int std;
    char sname[20];
} Student;

int main(int argc,char *argv[])
{
    if(argc !=2)
    {
        printf("filename\n");
        return -1;
    }
    //创建文件 打开文件
    int fd = open(argv[1],O_RDWR);
    int length = sizeof(Student);
    ftruncate(fd,length);
    //02创建映射区
    Student *stu = (Student*)mmap(NULL,length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(stu == MAP_FAILED)
    {
        perror("mmap error");
        return -1;
    }
    //3.读
    while(1){
           
            sleep(1);//每一秒修改映射区内容
            printf("sid=%d,sname = %s\n",stu->std,stu->sname);
    }
    //04 释放映射区
    munmap(stu,length);
    close(fd);
    return 0;
}