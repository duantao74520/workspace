#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    pid_t pid =fork();
    if(pid== 0){
        while(1)
        {
            printf("I am child ,pid = %d,ppid = %d\n",getpid(),getppid());
            sleep(3);
        }
    }
    else if(pid >0){
            printf("I am parent ,pid = %d,ppid = %d\n",getpid(),getppid());
        sleep(5);
        printf("I am die\n");
        
    }
    return 0;
}