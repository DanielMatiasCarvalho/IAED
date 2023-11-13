#include <stdio.h>
#include <string.h>

#define MAX 80

/*é susposto substituir por espacos ou "colar" a string*/

void apagaCaracter(char s[],char c);

int main()
{
    int i=0;
    char c,s[MAX],d;
    printf("Introduza a linha:\n");
    while((d=getchar())!= EOF && d!= '\n'){
        s[i]=d;
        i++;
    }
    s[i]='\0';
    printf("Introduza um caracter que deseja eliminar da linha:\n");
    c=getchar();
    apagaCaracter(s,c);
    printf("%s\n",s);
    return 0;
}
void apagaCaracter(char s[],char c)
{
    int i,j;
    for (i=0;s[i]!='\0';i++){
        if (s[i]==c){
            for(j=i;s[j]!='\0';j++)
                s[j]=s[j+1];
        }
    }
}