#include <stdio.h>

void piramide (int n)
{
    int l,c;
    for(l=0;l<n;l++){
        for(c=0;c<n-l-1;c++)
            printf("  ");
        for(c=0;c<l+1;c++){
            if(c)
                putchar(' ');
            printf("%d",c+1);
        }
        for(c=0;c<l;c++)
            printf(" %d",l-c);
        putchar('\n');
    }   
}
int main()
{
    int n;
    scanf("%d",&n);
    piramide(n);
    return 0;
}