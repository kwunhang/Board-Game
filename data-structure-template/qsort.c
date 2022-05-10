#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    struct pair pa = *(const struct pair*) a;
    struct pair pb = *(const struct pair*) b;
    if(pa.nums == pb.nums) return pa.idx - pb.idx;
    return pa.nums - pb.nums;
}

int cmp(const void* a,const void* b){
    room *pa = (room*) a;
    room *pb = (room*) b;
    return (pa->start-pb->start);
}

qsort(arr, matSize, sizeof(struct pair), cmp);
