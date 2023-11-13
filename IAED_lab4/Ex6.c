#include <stdio.h>
#include <string.h>

#define MAX 80
#define DIF 32
/*oq é standard input/output e como fuciona fgets*/

int leLinha(char s[]);
void maiusculas(char str[]);

int main()
{
    int i;
    char s[MAX];
    i=leLinha(s);
    maiusculas(s);
    printf("%s\n%d\n",s,i);
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
void maiusculas(char str[])
{
    int i;
    for (i=0;str[i]!='\0';i++)
        if (str[i]>='a' && str[i]<='z')
            str[i]=str[i]-DIF;
}