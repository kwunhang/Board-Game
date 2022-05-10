#include <stdlib.h>
#include <stdio.h>

struct AVLnode_s{
    int element;
    struct AVLnode_s *left;
    struct AVLnode_s *right;
    int height    
};
typedef struct AVLnode_s node;

int max(int a,int b){
    return (a>b)? a:b;
}

//if NULL return -1, the leave is start from 0
int height(node *N){
    if (N==NULL){
        return -1;
    }
    return N->height;
}

node *newNode(int data){
    node *anode=(node*)malloc(sizeof(node));
    anode->element=data;
    anode->left=NULL;
    anode->right=NULL;
    anode->height=0;
    return (anode);
}

node *rightRotate(node *y){
    node *x=y->left;
    node *T2 = x->right;

    x->right=y;
    y->left=T2;
    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;
    return (x);
}

node *leftRotate(node *x){
    node *y = x->right;
    node *T2 =y->left;

    y->left=x;
    x->right = T2;

    x->height = max(height(x->left),height(x->right))+1;
    y->height = max(height(y->left),height(y->right))+1;

    return y;
}

int getBalance(node *N){
    if(N==NULL) return 0;
    return height(N->left)-height(N->right);
}

node* insert(node *anode,int x){
    //1. Perform BST normal insertion
    if(anode == NULL){
        return(newNode(x));
    }
    if(x < anode->element)
        anode->left = insert(anode->left,x);
    else if(x > anode->element){
        anode->right=insert(anode->right,x);
    }
    else    //Equal elements are not allowed in BST
        return anode;

    //2. Update height 
    anode->height = 1+max(height(anode->left),height(anode->right));

    //3. check balance of BST
    int balance_factor = getBalance(anode);

    //Left Left Case
    if(balance_factor > 1 && x < anode->left->element)
        return rightRotate(anode);
    //Right Right Case
    if(balance_factor < -1 && x > anode->right->element)
        return leftRotate(anode);
    //Left Right Case
    if(balance_factor > 1 && x > anode->element){
        anode->left = leftRotate(anode->left);
        return rightRotate(anode);
    }
    //Right Left Case
    if(balance_factor < -1 && x < anode->right->element){
        anode->right = rightRotate(anode->right);
        return leftRotate(anode);
    }

    //return unchange node pointer
    return anode;
}