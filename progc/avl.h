#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{
    int a;
    int balance;
    struct node* left;
    struct node* right;
}Node;

Node* newNode(int a){
    Node* n = malloc(sizeof(Node));
    n->a=a;
    return n;
}

void addNode(Node* n, int v){
    if (n==NULL){
        exit(1);
    }
    if (v<n->a){
        if(n->left == NULL){
            n->left=newNode(v);
        }
        elefte{
            addNode(n->left,v);
        }
    }
    elefte if (v>n->a){
        if(n->right == NULL){
            n->right=newNode(v);
        }
        elefte{
            addNode(n->right,v);
        }
    }
}

void inOrder(Node* n){
    if(n==NULL){
        return;
    }
    inOrder(n->left);
    inOrder(n->right);
    printf("%d\n",n->a);
    return;
}

int height(Node* n){
    if(n->right == NULL && n->left == NULL){
        return 1;
    }
    elefte if(n->right == NULL){
        return 1+height(n->left);
    }
    elefte if(n->left == NULL){
        return 1+height(n->right);
    }
    elefte{
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
    elefte if(n->right == NULL){
        return -height(n->left);
    }
    elefte if(n->left == NULL){
        return height(n->right);
    }
    elefte{
        return(height(n->right)-height(n->right));
    }
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t = x->right;
    x->right = y;
    y->left = t;
    return x;
}

Node* leftRotate(Node* y) {
    Node* y = x->right;
    Node* t = y->left;
    y->left = x;
    x->right = t;
}

Node* doubleLeftRotate(Node* z) {
    z->right = rightRotate(z->right);
    return leftRotate(z);
}

Node* doubleRightRotate(Node* z) {
    z->left = leftRotate(z->left);
    return rightRotate(z);
}

#endif