#include <stdio.h>
#include <stdlib.h>

typedef struct stru_node {
    struct stru_node *next;
    int v;
} node;
/* constructs and returns a new node for the element e*/
node * new(int e);
/* remove the first element of the list and return the new head */
node * pop(node * head);
/* add integer e as the first element of the list and return the new head */
node * push(node * head, int e);
/* frees all memory associated with the list and returns NULL */
node * destroy(node * head);
/* print the elements of the integers in the list, one per line */
void print(node * head);
/*
int main()
{
    node * head=NULL;
    int i;
    while (scanf("%d",&i)>0 && i>0){
        head=push(head,c-'0');
    }
    print(head);
    destroy(head);
    return 0;
}
*/

node * new(int e){
    node *ptr;
    ptr=(node *)malloc(sizeof(node));
    ptr->v=e;
    ptr->next=NULL;
    return ptr;
}

node * pop(node * head){
    node *new_head=NULL;
    if (head != NULL){
        new_head=head->next;
    }
    free(head);
    return new_head;
}

node * push(node * head, int e){
    node * new_head;
    new_head=new(e);
    new_head->next=head;
    return new_head;
}

node * destroy(node * head){
    node * aux;
    while (head){
        aux=head->next;
        free(head);
        head=aux;
    }
    /* while(head!=NULL)
        head=pop(head);
       return NULL;*/ 
    return NULL;
}

void print(node * head){
    while(head){
        printf("%d\n",head->v);
        head=head->next;
    }
}