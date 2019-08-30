//kill my 第三个线程
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main()
{
  int i =0;
  pid_t pid,pid3;
  for(i =0 ;i<5;i++)
  {
      pid = fork();
      if(pid == 0)
      {
          printf("I am a Child :pid = %d,ppid =%d\n",getpid(),getppid());
          break;
      }
      if(i == 2)
      {
          pid3 = pid;
      }
  }
  if(i == 5)
  {
      sleep(3);
      printf("I am parent pid = %d ,I will kill xiaosan \n",getpid());
      kill(pid3,SIGKILL);
      while(1){sleep(1);}
  }
  if(i < 5 )
  {
      sleep(5);
      printf("I am child \n");
      while(1) {sleep(1);}
  }

}