#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int top;
    int size;
}Stack;

int createStack(Stack* astack,int size){
    astack->data = (int*)malloc(sizeof(int)*size);
    if(astack->data==NULL)
        return 0;
    astack->size = size;
    astack->top = -1;
    return 1;
}

void makeEmpty(Stack *astack){
    astack->top=-1;
}

int isEmpty(Stack *astack){
    if(astack->top<0)
        return 1;
    else
        return 0;
}

int isFull(Stack *astack){
    if(astack->top >=astack->size-1)
        return 1;
    else return 0;
}

int top(Stack* astack){
    if(!isEmpy(astack))
        return astack->data[astack->top];
    else
        return 0;
}

int pop(Stack* astack){
    if(!isEmpty(astack)){
        int adata = top(astack);
        astack->top--;
        return adata;
    }
    else 
        return 0;
}

//return 1 is push success,if fail return 0
int push(Stack* astack,int adata){
    if(!isFull(astack)){
        astack->top++;
        astack->data[astack->top] = adata;
        return 1;
    }
    else 
        return 0;
}