#include <stdio.h>

/*Divisor*/

int main()
{
    int numa, numb;
    printf("Introduz dois números inteiros:\n");
    scanf("%d%d",&numa,&numb);
    if (numa%numb == 0)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}