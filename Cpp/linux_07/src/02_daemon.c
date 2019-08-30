#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <dirent.h>
#define _FILE_NAME_FORMAT_ "%s/log/mydaemon.%ld" //定义文件格式化
void touchFile(int num)
{
    char *home_dir = getenv("HOME");
    printf("%s\n",home_dir);
    char  str_file_name[256] = {0};
    sprintf(str_file_name,_FILE_NAME_FORMAT_,home_dir,time(NULL));
    printf("%s\n",str_file_name);

    char dir_name[256] = {0};
    sprintf(dir_name,"%s/log",home_dir);
    DIR *dirp = opendir(dir_name);
    if(dirp == NULL)
    {
        mkdir(dir_name,0776);//没有 创建目录
    }
    int fd = open(str_file_name,O_CREAT|O_RDWR,0666);
    if(fd < 0)
    {
        perror("open error");
        exit(1);
    }
    close(fd);
}

int main()
{
    //创建子进程 ，父进程退出
    pid_t pid =fork();
    if(pid > 0 )
    {
        exit(1);
    }

    //当会长
    setsid();
    //设置掩码
    umask(0);
    //切换工作路径
    chdir(getenv("HOME"));//切换到HOME目录 用环境变量
    //关闭文件描述符
    //close(1),close(2),close(3);
    //执行核心逻辑
    struct itimerval myit = {{3,0},{5,0}};
    setitimer(ITIMER_REAL,&myit,NULL);//定时器 每隔一分钟创建一次
    struct sigaction act;
    act.sa_flags = 0;
    __sigemptyset(&act.sa_mask);
    act.sa_handler = touchFile;
    sigaction(SIGALRM,&act,NULL);
    while (1)
    {
        //每隔一分钟 在home/log创建文件
        sleep(1);

    }
    
    //退出
    return 0;
}