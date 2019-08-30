/*
利用stat 完成ls -l 的功能
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
int main(int argc ,char *argv[])//argc 代表的是参数长度 为空的时候==1
{

    if(argc !=2 )
    {
        printf("./a.out filename \n");
        return -1;
    }
    struct stat sb;
    //获取文件信息
    stat(argv[1],&sb);
    char stmode[11] = {"----------\0"};
    if(S_ISREG(sb.st_mode)) stmode[0] = '-';
    if(S_ISDIR(sb.st_mode)) stmode[0] = 'd';
    if(S_ISCHR(sb.st_mode)) stmode[0] = 'c';
    if(S_ISBLK(sb.st_mode)) stmode[0] = 'b';
    //解析权限
    
    if(sb.st_mode & S_IRUSR) stmode[1] ='r';
    if(sb.st_mode & S_IWUSR) stmode[2] = 'w';
    if(sb.st_mode & S_IXUSR) stmode[3] ='x';
    
     if(sb.st_mode & S_IRGRP) stmode[4] ='r';
    if(sb.st_mode & S_IWGRP) stmode[5] = 'w';
    if(sb.st_mode & S_IXGRP) stmode[6] ='x';

     if(sb.st_mode & S_IROTH) stmode[7] ='r';
    if(sb.st_mode & S_IWOTH) stmode[8] = 'w';
    if(sb.st_mode & S_IXOTH) stmode[9] ='x';
    //分析用户名 组名 可以通过函数得到  getuid getgrgid
    //时间获取 localtime
    struct tm *filetime = localtime(&sb.st_atime);
    char timebuf[20] ={0};
    sprintf(timebuf,"%ld月  %d %2d:%2d",filetime->tm_mon+1,filetime->tm_hour,filetime->tm_min);
    printf("%s %ld %s %s %ld %s %s\n ",stmode,sb.st_nlink,getpwuid(sb.st_uid)->pw_name,
            getgrgid(sb.st_gid)->gr_name,sb.st_size,timebuf,argv[1]);

    return 0;
	
}
