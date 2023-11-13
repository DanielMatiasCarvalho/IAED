#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 1000

typedef struct stru_node {
    struct stru_node *next;
    char *v;
} node;

/* constructs and returns a new node for the element e*/
node * new(const char *e);
/* remove the first element of the list and return the new head */
node * pop(node * head);
/* add integer e as the first element of the list and return the new head */
node * push(node * head,const char *e);
/* frees all memory associated with the list and returns NULL */
node * destroy(node * head);
/* print the elements of the integers in the list, one per line */
void print(node * head);

int main()
{
    char aux[MAX];
    node * head=NULL;
    while(scanf("%s",aux)&& !(aux[0]=='x' && aux[1]=='\0'))
        head=push(head,aux);
    print(head);
    destroy(head);
    return 0;
}

node * new(const char *e){
    node *ptr;
    ptr=(node *)malloc(sizeof(node));
    ptr->v=(char *)malloc((strlen(e)+1)*sizeof(char));
    strcpy(ptr->v,e);
    ptr->next=NULL;
    return ptr;
}

node * pop(node * head){
    node *new_head;
    if (head!=NULL){
        new_head=head->next;
        free(head->v);
    }
    free(head);
    return new_head;
}

node * push(node * head, const char *e){
    node * new_head;
    new_head=new(e);
    new_head->next=head;
    return new_head;
}

node * destroy(node * head){ /*podia fazer com o pop*/
    node * aux;
    while (head){
        aux=head->next;
        free(head->v);
        free(head);
        head=aux;
    }
    return NULL;
}

void print(node * head){
    while(head){
        printf("%s\n",head->v);
        head=head->next;
    }
}
