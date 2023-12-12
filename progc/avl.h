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
    n->left = n->right = NULL;
    return n;
}


void inOrder(Node* n){
    if(n==NULL){
        return;
    }
    inOrder(n->left);
    printf("%d\n",n->key);
    inOrder(n->right);
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
        return(height(n->right)-height(n->left));
    }
}

Node* rightRotate(Node* t) {
    Node* u = t->left;
    t->left = u->right;
    u->right = t;
    return u;
}

Node* leftRotate(Node* t) {
    Node* u = t->right;
    t->right = u->left;
    u->left = t;
    return u;
}

Node* doubleLeftRotate(Node* t) {
    t->right = rightRotate(t->right);
    return leftRotate(t);
}

Node* doubleRightRotate(Node* t) {
    t->left = leftRotate(t->left);
    return rightRotate(t);
}

Node* addNode(Node* n, int v){
    if (n==NULL){
        Node * new_node=newNode(v);
        return new_node;
    }
    if (v<n->key){
        n->left = addNode(n->left,v);
    
        if(balance(n)<=-2){
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