# include <stdio.h>

int main()
{
    char word[1000];
    char *p;

    scanf("%s",word);
    for (p=word;*p!='\0';p++)
        printf("%s\n",p);
    
    return 0;
}