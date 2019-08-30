#include <sys/stat.h>
#include <sys/types.h>
#include  <stdio.h>
#include <dirent.h>
#include <string.h>
int count = 0;

int dircount(char *dirname)
{
    //打开目录
    DIR *dirp = opendir(dirname);
    if(dirp == NULL )
    {
        perror("opendir err");
        return -1;
    }
    
    //循环读目录，如果是普通文件 那么count++ 如果是目录 那么递归
    struct dirent *dentp;
    while((dentp = readdir(dirp) )!= NULL ){
        printf("dirname : %s\n",dentp->d_name);
        if(dentp->d_type == DT_DIR){
            
           
            if(strcmp(".",dentp->d_name)==0|strcmp("..",dentp->d_name)==0)
                continue;
            //注意进程的工作路径 需要重新修改
            //使用dirname 拼接下一级子目录
             char new_dir_name[256] = {0};
             sprintf(new_dir_name,"%s/%s",dirname,dentp->d_name);
             dircount(new_dir_name);

             
        }
        //如果是普通文件
        if(dentp->d_type == DT_REG)
            count++;
    }
    return 0;
}

 int main(int argc,char *argv[])
 {
     if(argc !=2 )
    {
        printf("./a.out dirname \n");
        return -1;
    }
    //用递归的方式读取
    dircount(argv[1]);
    printf("regular file num: %d\n",count);
 }