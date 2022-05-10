#include <stdio.h>
#include <stdlib.h>

typedef struct heapStruct{
    int *element;
    int size;
    int capacity;
}Heap;

void insertMaxHeap(Heap *h,int item){
    if(h->size==h->capacity)    exit(1);
    int i=h->size;
    while(i!=0 && item>h->element[(i-1)/2]){
        h->element[i]=h->element[(i-1)/2];
        i=i-1/2;
    }
    h->element[i]=item;
    h->size++;
}

int removeMaxAndInsert(Heap *h,int item){
    if(h->size==0||h->size!=h->capacity)  exit(2);     //the heap is null or the function is called while the heap is not full
    int i;
    int parent,child;
    i = h->element[0];
    parent=0;
    child=1;
    while(child<h->size){
        if(child+1<h->size&&h->element[child]<h->element[child+1]){    //have two child and right child is larger
            child++;
        }
        if(item>=h->element[child])   break;
        h->element[parent]=h->element[child];
        parent=child;
        child=parent*2+1;
    }
    h->element[parent]=item;
    return i;
}

void maxheapify(Heap *h,int i){
    if(h->size==1) return;
    if(h->size==0) exit(1);                      //GGGGGGGGGGGGGGGGG
    else{
        int largest=i;
        int l= i*2+1;
        int r=i*2+2;
        if(l<h->size&&h->element[largest]<h->element[l]){
            largest=l;
        }
        if(r<h->size&&h->element[largest]<h->element[r]){
            largest=r;
        }
        if(largest!=i){
            int temp=h->element[i];
            h->element[i]=h->element[largest];
            h->element[largest]=temp;
            maxheapify(h,largest);

        }

    }
}
