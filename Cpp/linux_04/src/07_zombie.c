//僵尸进程
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    pid_t pid =fork();
    if(pid== 0){
        printf("I am child ,pid = %d,ppid = %d\n",getpid(),getppid());
        sleep(3);
        printf("i am child ,i will die\n");
    }
    else if(pid >0){
        while(1){
        printf("I am parent ,pid = %d,ppid = %d\n",getpid(),getppid());
        sleep(1);
        }
        
     
    }
    return 0;
}