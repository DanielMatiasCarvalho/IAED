#include <stdlib.h>
#include <stdio.h>

#define INIT_CAP 4

typedef struct {
    int *v; /*contents of the stack*/
    int cap; /* capacity of v, i.e. how many elements can fit in v */
    int sz; /* number of elements currently stored in v */
} stack;

stack* build();                 /* builds a new empty stack with initial capacity 4 */
void push(stack * s, int e);    /* pushes integer e on top of the stack  (reallocate v if necessary) */
int top(stack * s);             /* returns top element in the stack */
int pop(stack * s);             /* removes top element from the stack and return it
                                    (not necessary to reallocate v) */
int is_empty(stack * s);        /* returns 1 iff s represents the empty stack, returns 0 otherwise */
void destroy(stack * s);        /* frees the memory associated with the stack */

stack* build(){
    stack *s=(stack *)malloc(sizeof(stack)); /*não entendo, isto é necessário?*/
    s->cap=INIT_CAP;
    s->v=(int *)malloc(sizeof(int)*s->cap);
    s->sz=0;
    return s;
}

int is_empty(stack * s){
    return(s->sz==0);
}

int top(stack * s){
    return s->v[s->sz-1];
}

void push(stack * s, int e){
    int i;
    if (s->cap==s->sz){
        s->cap+=INIT_CAP;
        s->v=(int*) realloc(s->v,sizeof(int)*s->cap);
    }
    s->v[s->sz]=e;
    s->sz++;
}

int pop(stack * s){
    return s->v[--s->sz];
}

void destroy(stack *s){
    free(s->v);
    free (s);
}