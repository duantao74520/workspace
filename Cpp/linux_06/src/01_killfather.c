//kill my father
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
  pid_t pid;
  for(i =0 ;i<5;i++)
  {
      pid = fork();
      if(pid == 0)
      {
          printf("I am a Child :pid = %d,ppid =%d\n",getpid(),getppid());
          break;
      }
  }
  if(i == 5)
  {
      sleep(3);
      printf("I am parent I will die\n");
      while(1){sleep(1);}
  }
  if(i==2)
  {
      sleep(5);
      kill(getppid(),SIGKILL);
      while(1) {sleep(1);}
  }

}