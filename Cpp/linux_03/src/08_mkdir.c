#include <sys/stat.h>
#include <sys/types.h>
#include  <stdio.h>
 int main(int argc,char *argv[])
 {
    if(argc !=2 )
    {
        printf("./a.out filename \n");
        return -1;
    }
    mkdir(argv[1],0766);
    return 0;

 }