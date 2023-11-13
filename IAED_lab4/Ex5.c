#include <stdio.h>
#include <string.h>

#define MAX 80

int leLinha(char s[]);

int main()
{
    int i;
    char s[MAX];
    i=leLinha(s);
    printf("%s\n%d",s,i);
    return 0;
}
int leLinha(char s[])
{
    int i=0;
    char c;
    while((c=getchar())!= EOF && c!= '\n'){
        s[i]=c;
        i++;
    }
    s[i]='\0';
    return i;
}