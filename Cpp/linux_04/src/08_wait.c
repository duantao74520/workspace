//僵尸进程
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
   pid_t pid =fork();
    if(pid == 0){
        printf("I am a child ,I will die \n");
        sleep(5);
       // exit(102);//正常死亡
       while(1)
       {sleep(1);}
    }
    else if(pid >0){
        printf("I am parent ,wait for child die;\n");
        int status;//wait 会返回一个值 返回死亡原因
        pid_t wpid = wait(&status);//wait 阻塞了 回收僵尸进程资源 查看死亡原因
        printf("wait ok ,wpid = %d,pid = %d\n",wpid,pid);

        if(WIFEXITED(status)){
            printf("child exit with %d\n",WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("child exit with %d\n",WTERMSIG(status));
 
        }
        while(1)
        {
            sleep(1);
        }
    }
    return 0;
}