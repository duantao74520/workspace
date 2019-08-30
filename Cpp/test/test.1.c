#include <stdio.h>
#include <stdlib.h>
typedef struct t
{
    int a;
    int b;
} ;

int main()
{
    struct t *p = (struct t *)malloc(sizeof(struct t));
    p->a =12;
    p->b=12;
    printf("num= %d, addr= %d\n",p->a,p);
    free(p);
    printf("num= %d, addr= %d\n",(*p).a,p);
    p->a =11.28;

    printf("num= %d, addr= %d\n",(*p).a,p);
    return 0;
}