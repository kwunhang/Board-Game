#include <stdio.h>
#include <stdlib.h>

struct node_s{
    int data;
    struct node_s *next;
};

typedef struct node_s node;

node *create_stack(){
    node *emptyStack;
    emptyStack = (node*)malloc(sizeof(node));
    emptyStack -> next = NULL;
    return emptyStack;
}

void Push(int inputdata,node *stack){
    node *newnode = (node*)malloc(sizeof(node));
    newnode->data=inputdata;
    newnode->next=stack->next;
    stack->next=newnode;
}

int Pop(node *stack){
    int temp;
    node *toBePopped;
    if(stack->next!=NULL){
        temp=stack->next->data;
        toBePopped=stack->next;
        stack->next=stack->next->next;
        free(toBePopped);
        return temp;
    }
    else
        return 0;
}

int top(node *stack){
    if(stack->next!=NULL)
        return stack->next->data;
    else
        return 0;
}

//return 1 if stack is empty, if not return 0
int is_empty(node *stack){
    return(stack->next==NULL);
}

//clear the link list, the entry would still be here
void makeEmpty(node *stack){
    int temp;
    while(!(is_empty(stack))){
        temp = Pop(stack);
    }
    return;
}