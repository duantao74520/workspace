//execl 函数族  实现ls
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    //int execlp(const char *file, const char *arg, .../* (char *) NULL */); 
    //execlp("ls","ls","-l",NULL);//最后要加一个NULL
    //execl("/bin/ls","ls","-l",NULL);//必须要有绝对路径
    pid_t pid = fork();
    if(pid ==0)//子进程
    {
    execl("./04_shared","04_shared",NULL);//相当于在此处运行别的函数
    //不需要判断返回值 回来只有错误
    perror("exec err");
    }
    else
    {
        execl("/bin/ls","ls","-l",NULL);//必须要有绝对路径
    }
    

    return 0;
}