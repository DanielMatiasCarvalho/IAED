#include <stdio.h>
#include <stdlib.h>
#include "Exec1.c"

int is_eq(node *h1, node *h2);   /* compara duas listas */
node * rev(node * head);         /* devolve uma nova lista que corresponda a lista dada invertida */

int main()
{
    char c;
    node * head=NULL;
    node * head2=NULL;
    while ((c=getchar())!='\n' && c!=EOF){
        head=push(head,c);
    }
    head2=rev(head);
    if (is_eq(head,head2))
        printf("yes\n");
    else    
        printf("no\n");
    destroy(head); /*porque nao se faz dois destroy?*/
    return 0;
}

int is_eq(node *h1,node *h2)
{
    while (h1 && h2){
        if (h1->v!=h2->v)
            return 0;
        h1=h1->next;
        h2=h2->next;
    }
    return 1;
}

node * rev(node * head){
    node * head2=NULL;
    while (head){
        head2=push(head2,head->v);
        head=head->next;
    }
    return head2;
}