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
    if(access(argv[1],R_OK) == 0) printf("可读\n");
    if(access(argv[1],W_OK) == 0) printf("可写\n");
    if(access(argv[1],X_OK) == 0) printf("可执行\n");
    if(access(argv[1],F_OK) == 0) printf("文件存在\n");

    return 0;
	
}
