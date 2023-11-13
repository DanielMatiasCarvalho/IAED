#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct str_node  {
    struct str_node *next, *previous;
    char *c;
} node;

typedef struct  {
    struct str_node *head, *last;
} list;

node * new(char *e);
list* mk_list();                 /* cria nova lista vazia */
void  free_list(list *l);        /* liberta toda a memoria associada a lista */
void  add_last(list *l, char *c); /* adiciona o char c como o ultimo elemento da lista */
/* Checks if string e is in the list. Returns 1 if string e is in the list. Oterhwise, returns 0. */
int lookup(node *head, const char *e);

int main()
{
    list * lst;
    node *aux;
    int num=0;
    char c[1000],d=' ';
    lst=mk_list();
    while(scanf("%s",c)>0){
        if (lookup(lst->head,c)==0){
            num++;
            add_last(lst,c);
        }
    }
    printf("%d",num);
    for(aux=lst->head;aux!=NULL;aux=aux->next)
    {
        printf("%s\n",aux->c);
    }
    free_list(lst);
    return 0;
}

node * new(char *e){
    node *ptr;
    ptr=(node *)malloc(sizeof(node));
    ptr->c=(char *)malloc(sizeof(char)*(1+strlen(e)));
    strcpy(ptr->c,e);
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

void add_last(list*l,char *c){
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

int lookup(node *head,const char *e)
{
    node *aux;
    for(aux=head;aux!=NULL;aux=aux->next){
        if (strcmp(aux->c,e)==0){
            return 1;
        }
    }
    return 0;
}