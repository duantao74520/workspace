/*
测试一个进程最多打开多少个文件
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc ,char *argv[])//argc 代表的是参数长度 为空的时候==1
{

    int num =3;
    char  name[128] = {0};
    while(1)
    {
        sprintf(name,"temp_%04d",num++);
        if(open(name,O_RDONLY|O_CREAT,0666)<0){
            perror("open err");
            break;
        }
        
    }
    printf("num == %d\n",num);
    return 0;
	
}

//结果 最大只能打开 1024-3个