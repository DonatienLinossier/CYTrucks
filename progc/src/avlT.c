#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avlT.h"

NodeT* newNodeT(char* city_name, int num_steps, int firsts){//Creates a new NodeT with the city_name as a key
    NodeT* n = malloc(sizeof(NodeT));
    n->key=num_steps;
    n->left = n->right = NULL;
    n->city = malloc(strlen(city_name) + 1);
    strcpy(n->city, city_name);
    n->num_firsts = firsts;
    n->height=0;
    return n;
}


void inOrderT(NodeT* n, int* count, NodeT* results[10]) {
    if (n == NULL || *count >= 10) return;
    inOrderT(n->right, count, results);
    if (*count < 10) {
        results[*count]=n;
        *count += 1;
    }
    inOrderT(n->left, count, results);
}

int heightT(NodeT* n){//Returns the height of the AVL tree(Max number of sons)
    if(n==NULL){
        return 0;
    }
    else if(n->right == NULL && n->left == NULL){
        return 1;
    }
    else if(n->right == NULL){
        return 1+n->left->height;
    }
    else if(n->left == NULL){
        return 1+n->right->height;
    }
    else{
        return 1+fmax(n->left->height, n->right->height);
    }
}

int balanceT(NodeT* n){//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)
    if(n==NULL){
        return(0);
    }

    else{
        return (heightT(n->right)-heightT(n->left));
    }
}

int getMin(int array[],int length){
    if(array==NULL){
        exit(1);
    }
    int minIndex=0;
    int minValue=array[0];
    for(int i = 1; i<length;i++){
        if(array[i]<minValue){
            minValue=array[i];
            minIndex=i;
        }
    }
    return minIndex;
}

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeTs

NodeT* rightRotateT(NodeT* y){//To use when the right branch is too heavy and straight
    NodeT* x = y->left;
    NodeT* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = heightT(y);
    x->height = heightT(x);

    return x;
}

NodeT* leftRotateT(NodeT* x){//To use when the left branch is too heavy and straight
    NodeT* y = x->right;
    NodeT* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = heightT(x);
    y->height = heightT(y);

    return y;
}

void freeNodeT(NodeT* node) {
    if (node == NULL) return;
    
    freeNodeT(node->left);
    freeNodeT(node->right);
    free(node->city);  // Free the allocated memory for the city name
    free(node);
}

int compareT(const void* c, const void* d) {
    const NodeT* a = *(const NodeT **)c;
    const NodeT* b = *(const NodeT **)d;
    return strcmp(a->city,b->city);
}

NodeT* addNodeT(NodeT* node, char* city_name, int num_steps, int num_firsts){
    // Find the correct position to addNodeT the node and addNodeT it
    if (node == NULL)
        return newNodeT(city_name, num_steps, num_firsts);
    if (num_steps < node->key)
        node->left = addNodeT(node->left, city_name, num_steps, num_firsts);
    else if (num_steps > node->key)
        node->right = addNodeT(node->right, city_name, num_steps, num_firsts);
    else{
        
    }

    // Balance the tree
    node->height = heightT(node);

    int balance = balanceT(node);

    if (balance < -1 && num_steps < node->left->key)
        return rightRotateT(node);

    if (balance > 1 && num_steps > node->right->key)
        return leftRotateT(node);

    if (balance < -1 && num_steps > node->left->key) {
        node->left = leftRotateT(node->left);
        return rightRotateT(node);
    }

    if (balance > 1 && num_steps < node->right->key) {
        node->right = rightRotateT(node->right);
        return leftRotateT(node);
    }

    //printf("return\n");
    return node;
}

