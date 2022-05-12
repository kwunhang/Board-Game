#include<stdio.h>
#include<stdlib.h>

struct data{
    int data;
    int state;
};


int hash(int item){
    return item%size;
}
