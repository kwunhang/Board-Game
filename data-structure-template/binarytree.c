#include <stdlib.h>
#include <stdio.h>

struct node_s{
    int element;
    struct node_s *leftChild;
    struct node_s *rightChild;
};
typedef struct node_s node;

void preorder(node *t){
    if(t!=NULL){
        printf("%d",t->element);
        preorder(t->leftChild);
        preorder(t->rightChild);
    }
}

void inorder(node *t){
    if(t!=NULL){
        inorder(t->leftChild);
        printf("%d",t->element);
        inorder(t->rightChild);
    }
}

void postorder(node* t){
    if(t!=NULL){
        postorder(t->leftChild);
        postorder(t->rightChild);
        printf("%d",t->element);
    }
}
