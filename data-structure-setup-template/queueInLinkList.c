#include <stdio.h>
#include <stdlib.h>

struct node_s{
    int data;
    struct node_s *next;
};
typedef struct node_s node;

typedef struct{
    node *head, *tail;
}Queue;

node *newNode(int adata){
    node *temp = (node*)malloc(sizeof(node));
    temp->data = adata;
    temp->next = NULL;
    return temp;
}

Queue *createQueue(){
    Queue *newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->head=NULL;
    newQueue->tail=NULL;
    return newQueue;
}

void enQueue(Queue* aqueue, int adata){
    node *temp = newNode(adata);

    if(aqueue -> tail==NULL){
        aqueue->head = temp;
        aqueue->tail = temp;
        return;
    }
    aqueue->tail->next = temp;
    aqueue->tail=temp;
    return;
}

void deQueue(Queue *aqueue){
    if(aqueue ->head == NULL)
        return;
    node *temp = aqueue -> head;
    aqueue->head = aqueue->head->next;

    if(aqueue->head==NULL)
        aqueue->tail = NULL;
    free(temp);
    return;
}