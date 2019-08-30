/*
测试stat的功能 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc ,char *argv[])//argc 代表的是参数长度 为空的时候==1
{

    if(argc !=2 )
    {
        printf("./a.out filename \n");
        return -1;
    }
    struct stat sb;
    //sb.
    
    stat(argv[1],&sb);
    return 0;
	
}
