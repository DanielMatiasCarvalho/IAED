#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct str_node  {
    struct str_node *next, *previous;
    char c;
} node;

typedef struct  {
    struct str_node *head, *last;
} list;

node * new(char e);
list* mk_list();                 /* cria nova lista vazia */
void  free_list(list *l);        /* liberta toda a memoria associada a lista */
void  add_last(list *l, char c); /* adiciona o char c como o ultimo elemento da lista */
int   is_paly(const list *ls);   /* calcula se a dada lista e um palindromo */

int main()
{
    list * lst;
    char c;
    lst=mk_list();
    while(((c=getchar())!='\n' && c!=EOF)){
        add_last(lst,c);
    }
    if (is_paly(lst))
        printf("yes\n");
    else    
        printf("no\n");
    free_list(lst);
    return 0;
}

node * new(char e){
    node *ptr;
    ptr=(node *)malloc(sizeof(node));
    ptr->c=e;
    ptr->next=NULL;
    ptr->previous=NULL;
    return ptr;
}

list * mk_list(){
    list *l;
    l=(list *) malloc(sizeof(list));
    l->head=NULL;
    l->last=NULL;
    return l;
}

void free_list(list *l){
    node * aux;
    while(l->head){
        aux=l->head->next;
        free(l->head);
        l->head=aux;
    }
    free(l);
}

void add_last(list*l,char c){
    node * ptr;
    ptr=new(c);
    if (l->head==NULL){ /*vazia*/
        l->head=ptr;
        l->last=l->head;
    }
    else{
        ptr->previous=l->last;
        l->last->next=ptr;
        l->last=ptr;
    }
    /* new->previous=l->last;
        if(l->last!=NULL)
            l->last->next=new;
        l->last=new;
        if(l->head==NULL)
            l->head=new;
    */
}

int is_paly(const list *ls){
    node *h,*l;
    for (h=ls->head,l=ls->last;h!=l && h!=l->next;h=h->next,l=l->previous){
        if(h->c!=l->c)
            return 0;
    }
    return 1;
}