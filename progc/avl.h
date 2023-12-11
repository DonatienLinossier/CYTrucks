#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
    int key;
    int balance;
    struct node* left;
    struct node* right;
}Node;

Node* newNode(int a){
    Node* n = malloc(sizeof(Node));
    n->key=a;
    return n;
}


void inOrder(Node* n){
    if(n==NULL){
        return;
    }
    inOrder(n->left);
    inOrder(n->right);
    printf("%d\n",n->key);
    return;
}

int height(Node* n){
    if(n->right == NULL && n->left == NULL){
        return 1;
    }
    else if(n->right == NULL){
        return 1+height(n->left);
    }
    else if(n->left == NULL){
        return 1+height(n->right);
    }
    else{
        return 1+fmax(height(n->left),height(n->right));
    }
}

int balance(Node* n){
    if(n==NULL){
        exit(1);
    }
    if(n->right == NULL && n->left == NULL){
        return 0;
    }
    else if(n->right == NULL){
        return -height(n->left);
    }
    else if(n->left == NULL){
        return height(n->right);
    }
    else{
        return(height(n->right)-height(n->right));
    }
}

Node* rightRotate(Node* y) {
    printf("r\n");
    Node* x = y->left;
    Node* t = x->right;
    x->right = y;
    y->left = t;
    return x;
}

Node* leftRotate(Node* x) {
    printf("l\n");
    Node* y = x->right;
    Node* t = y->left;
    y->left = x;
    x->right = t;
}

Node* doubleLeftRotate(Node* z) {
    printf("dl\n");
    z->right = rightRotate(z->right);
    return leftRotate(z);
}

Node* doubleRightRotate(Node* z) {
    printf("dr\n");
    z->left = leftRotate(z->left);
    return rightRotate(z);
}

Node* addNode(Node* n, int v){
    if (n==NULL){
        Node * new_node=newNode(v);
        return new_node;
    }
    if (v<n->key){
        printf("a\n");
        n->left = addNode(n->left,v);
        printf("%d\n",balance(n));
        if(balance(n)<=-2){
            printf("%d\n",balance(n));
            if(v < n->left->key){
                n = rightRotate(n);
            }
            else {
                n = doubleRightRotate(n);
            }
        }
    }
    else if (v>n->key){
        n->right = addNode(n->right,v);
        if(balance(n)>=2){
            if(v > n->right->key){
                n = leftRotate(n);
            }
            else {
                n = doubleLeftRotate(n);
            }
        }
    }
    return n;


}


#endif