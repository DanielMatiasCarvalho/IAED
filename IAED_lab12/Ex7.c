#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HBASE 31
#define TABDIM 101

typedef struct str_node  {
    struct str_node *next, *previous;
    char *c;
} node;

typedef struct  {
    struct str_node *head, *last;
} list;

typedef struct  {    
  list* table[TABDIM];    /*mudei para lista porque achei que fazia mais sentido*/
  int nitem;
} symtab;

static unsigned hashvalue(char *word) {
    unsigned hval = 0;
    for(hval = 0; *word; )
        hval = *(word++) + HBASE * hval;
    return hval % TABDIM;
}

node * new(char *e);
list* mk_list();                 /* cria nova lista vazia */
void  free_list(list *l);        /* liberta toda a memoria associada a lista */
void  add_last(list *l, char *c); /* adiciona o char c como o ultimo elemento da lista */
/* Checks if string e is in the list. Returns 1 if string e is in the list. Oterhwise, returns 0. */
int lookup(node *head, const char *e);
static unsigned hashvalue(char *word);
/* Creates and initializes a new symbol table. */
symtab* createTable();
int lookupTable(symtab *tab,char *e);
void insertTable(symtab *tab, char *e);
void printTable(symtab *tab);

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
    int i;
    lst=mk_list();
    symtab *tab=createTable();
    while(scanf("%s",c)>0){
        if (lookupTable(tab,c)==0){
            insertTable(tab,c);
        }
    }
    printTable(tab);
    for(i=0;i<TABDIM;i++){
        free_list(tab->table[i]);
    }
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

static unsigned hashvalue(char *word) { /*nao entendi o raciocionio*/
    unsigned hval = 0;
    for(hval = 0; *word; )
        hval = *(word++) + HBASE * hval;
    return hval % TABDIM;
}

symtab *createTable()
{
    int i;
    symtab *tab;
    tab->nitem=0;
    for(i=0;i<TABDIM;i++){
        tab->table[i]=mk_list();
    }
    return tab;
}

int lookupTable(symtab *tab,char *e){
    int i,res;
    i=hashvalue(e);
    res=lookup(tab->table[i]->head,e);
    return res;
}

void insertTable(symtab *tab, char *e){
    int i=hashvalue(e);
    if(!lookup(tab->table[i]->head,e))
        add_last(tab->table[i],e);
    tab->nitem++;
}

void printTable(symtab *tab){
    int i;
    node *aux;
    printf("%d",tab->nitem);
    for(i=0;i<TABDIM;i++){
        for(aux=tab->table[i]->head;aux!=NULL;aux=aux->next)
        {
            printf("%s\n",aux->c);
        }
    }
}