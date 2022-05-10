#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *data;
    int head;
    int tail;
    int num;
    int size;
}Queue;

int createQueue(Queue* aqueue, int size){
    aqueue->data = (int*)malloc(sizeof(int)*size);
    if(aqueue->data==NULL)
        return 0 ;
    aqueue->head=0;
    aqueue->tail=-1;
    aqueue->num=0;
    aqueue->size=size;
    return 1;
}

int enqueue(Queue *aqueue,int adata){
    if(aqueue->num < aqueue->size){
        aqueue->tail = (aqueue->tail + 1) %aqueue->size;
        aqueue->data[aqueue->tail]=adata;
        return 1;
    }
    else return 0;
}

int dequeue(Queue* aqueue){
    if(aqueue->num > 0){
        int adata = aqueue->data[aqueue->head];
        aqueue->head = (aqueue->head+1)%aqueue->size;
        aqueue->num--;
        return adata;
    }
    else return 0;
}

int isEmpty(Queue *aqueue){
    return (aqueue->num==0);
}

int isFull(Queue *aqueue){
    return (aqueue->num==aqueue->size);
}

int front(Queue* aqueue){
    return aqueue->data[aqueue->head];
}

void makeEmpty(Queue* aqueue){
    aqueue->head=0;
    aqueue->num=0;
    aqueue->tail=-1;
}