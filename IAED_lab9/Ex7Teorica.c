#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
#define MAXWORD 10000

int main()
{
    int i,n;
    char buffer[MAXCHAR];
    char *words[MAXWORD];

    for (i=0;i<MAXWORD;i++){
        words[i]=NULL;
    }

    for(n=0;n<MAXWORD && scanf("%s",buffer)>0;n++){
        words[n]= (char *) malloc(sizeof(char) * (strlen(buffer)+1));
        strcpy(words[n],buffer);
    }
    for(i=n-1;i >= 0;i--)
        printf("%s\n",words[i]);
    for (i=0;i<n;i++)
        free(words[i]);

    return 0;
}