#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct node{//Declares the node structure used for AVL trees
    int key;
    int balance;
    struct node* left;
    struct node* right;
}Node;

Node* newNode(int a){//Creates a new node with "a" as a key
    Node* n = malloc(sizeof(Node));
    n->key=a;
    n->left = n->right = NULL;
    return n;
}


void inOrder(Node* n){//Displays the values in the AVL tree in ascending order
    if(n==NULL){
        return;
    }
    inOrder(n->left);
    printf("%d\n",n->key);
    inOrder(n->right);
    return;
}

int height(Node* n){//Returns the height of the AVL tree(Max number of sons)
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

int balance(Node* n){//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)
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

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the nodes

Node* rightRotate(Node* n){//To use when the right branch is too heavy and straight
    Node* u = n->left;
    n->left = u->right;
    u->right = n;
    return u;
}

Node* leftRotate(Node* t){//To use when the left branch is too heavy and straight
    Node* u = n->right;
    n->right = u->left;
    u->left = n;
    return u;
}

Node* doubleLeftRotate(Node* n){//To use when the right branch is too heavy and is bended
    n->right = rightRotate(n->right);
    return leftRotate(n);
}

Node* doubleRightRotate(Node* n){//To use when the left branch is too heavy and is bended
    n->left = leftRotate(n->left);
    return rightRotate(n);
}

Node* addNode(Node* n, int v){//Adds a node of key v to the AVL Tree, then fixes the balance of the tree using rotations if needed
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