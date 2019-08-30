//文件读写锁

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define _FILE_NAME_ "/home/duan/temp.lock"

int main()
{
    int fd = open(_FILE_NAME_,O_RDWR|O_CREAT,0664);
    if(fd < 0 )
    {
        perror(" open error");
        return -1;
    }
    struct flock lk;
    lk.l_type = F_WRLCK;
    lk.l_whence = SEEK_SET ;
    lk.l_start = 0;
    lk.l_start = 0;
    if(fcntl(fd,F_SETLK,&lk)<0)
    {
        perror("get lock error");
        exit(1);
    }
    //核心逻辑

    return 0;

}