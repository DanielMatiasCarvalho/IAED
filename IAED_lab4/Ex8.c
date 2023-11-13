#include <stdio.h>
#include <string.h>

#define MAX 100

int main(){
    int len,i;
    char n1[MAX],n2[MAX];
    printf("Introduz um número:\n");
    fgets(n1,MAX,stdin);
    printf("Introduz um número:\n");
    fgets(n2,MAX,stdin);
    len=strlen(n1)-1;
    for (i=0;i<=len;i++){
        if (n1[i]>n2[i])
            printf("%s",n1);
        else if (n1[i]<n2[i])
                printf("%s",n2);
    }
    return 0;
}