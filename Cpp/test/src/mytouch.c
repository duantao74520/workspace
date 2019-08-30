/*
touch命令有两个功能：
  一是用于把已存在文件的时间标签更新为系统当前的时间（默认方式），它们的数据将原封不动地保留下来；
 二是用来创建新的空文件。
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc ,char *argv[])//argc 代表的是参数长度 为空的时候==1
{
    if(argc !=2 )
    {
        printf("./a.out filename \n");
        return -1;
    }
    close(STDOUT_FILENO);
    int fd = open(argv[1],O_CREAT|O_TRUNC|O_WRONLY,0666);//umask = 002取补码
    printf("%d\n",fd);
    write(fd,"hello_word\0",11);
    fflush(stdout);//刷新缓冲区
    close(fd);
    return 0;
	
}
