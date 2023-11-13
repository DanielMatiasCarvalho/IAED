#include <stdio.h>

void quadrado (int n)
{
    int l,c;
    for(l=0;1<n;l++){
        for(c=0;c<n;c++){
            if (c!=0)
                printf("\t");
            printf("%d",l+c+1);
        }
        printf("\n");
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    quadrado(n);
    return 0;
}