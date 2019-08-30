//mmap 共享存储映射 父子进程通信 匿名映射
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
int main()
{
    //创建映射区 

    int *mem = (int*)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);//匿名映射 比较好用 不用开文件
    if(mem == MAP_FAILED)
    {
        perror("mmap error");
        return -1;
    }
    //创建子进程
    pid_t  pid = fork();
    if(pid==0)
    {
        *mem = 100;
        printf("child,*mem =%d\n",*mem);
        sleep(3);
        printf("child,*mem =%d\n",*mem);
    }
    else if(pid>0)
    {
        sleep(1);
        printf("parent *mem =%d\n",*mem);
        *mem =1001;
        printf("parent *mem =%d\n",*mem);
        wait(NULL);
    }
    munmap(mem,4);
    return 0;
}