#include <stdio.h>
#include <stdlib.h>

typedef struct heapStruct{
    int *element;
    int size;
    int capacity;
}Heap;


int minDelection(Heap *h){
    int temp,item;
    int parent,child;
    item = h->element[0];
    temp=h->element[h->size-1];
    h->size--;
    parent = 0;
    child = 1;
    while(child<=(h->size-1)){
        if((child<(h->size-1))&&(h->element[child]>h->element[child+1])){
            child++;
        }
        if(temp<=h->element[child]) break;
        h->element[parent]=h->element[child];
        parent=child;
        child=child*2+1;
    }
    h->element[parent]=temp;
    return item;
}

void freeHeap(Heap *h){
    free(h->element);
    free(h);
}

void insertHeap(Heap *h,int item){
    int i;
    i=h->size;
    while((i!=0)&&(item<h->element[(i-1)/2])){
        h->element[i]=h->element[(i-1)/2];
        i=(i-1)/2;
    }
    h->element[i]=item;
    h->size++;
}

void minheapify(Heap *h,int i){
    if(h->size==1) return;
    else{
        int smallest=i;
        int l= i*2+1;
        int r=i*2+2;
        if(l<h->size&&h->element[l]<h->element[smallest]){
            smallest=l;
        }
        if(r<h->size&&h->element[r]<h->element[smallest]){
            smallest=r;
        }
        if(smallest!=i){
            int temp=h->element[i];
            h->element[i]=h->element[smallest];
            h->element[smallest]=temp;
            minheapify(h,smallest);
        }

    }
}

int main(){
    int i;
    Heap* hp=(Heap*)malloc(sizeof(Heap));
    for(i=hp->size/2 -1;i>=0;i--){ 
        minheapify(hp,i);
    }
}