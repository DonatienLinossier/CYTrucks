#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avlT.h"

#define NUM_VALUES_T 10

// Function to create a new AVL tree node with the given route_id and distance
NodeT* newNodeT(char* city_name, int num_steps, int firsts){
    NodeT* n = malloc(sizeof(NodeT));
    n->key=num_steps;
    n->left = n->right = NULL;
    n->city = malloc(strlen(city_name) + 1);
    strcpy(n->city, city_name);
    n->num_firsts = firsts;
    n->height=0;
    return n;
}

void printNodeT(NodeT* n) {
    if (n == NULL)exit(1);
    printf("%s;%d;%d\n", n->city, n->key, n->num_firsts);
}

// Function to add the NUM_VALUES_T biggest values of the AVL tree in ascending order to an array
void inOrderT(NodeT* n, int* count, NodeT* results[]) {
    if (n == NULL || *count >= NUM_VALUES_T) return;
    inOrderT(n->right, count, results);
    if (*count < NUM_VALUES_T) {
        results[*count]=n;
        *count += 1;
    }
    inOrderT(n->left, count, results);
}

// Function to calculate the height of the AVL tree
int heightT(NodeT* n){
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

// Function to calculate the balance of the AVL Tree
int balanceT(NodeT* n){
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

// Right rotation to balance the AVL Tree when the left branch is too heavy and straight
NodeT* rightRotateT(NodeT* y){
    NodeT* x = y->left;
    NodeT* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = heightT(y);
    x->height = heightT(x);

    return x;
}

// Left rotation to balance the AVL Tree when the right branch is too heavy and straight
NodeT* leftRotateT(NodeT* x){
    NodeT* y = x->right;
    NodeT* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = heightT(x);
    y->height = heightT(y);

    return y;
}

// Left then right rotate to balance the AVL Tree when the right branch is too heavy but bended
NodeT* doubleRightRotateT(NodeT* n){
    n->left = leftRotateT(n->left);
    return rightRotateT(n);
}

// Right then left rotate to balance the AVL Tree when the left branch is too heavy but bended
NodeT* doubleLeftRotateT(NodeT* n){
    n->right = rightRotateT(n->right);
    return leftRotateT(n);
}

//Function that frees the whole tree
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

// Function to addNodeT a new node to the AVL tree
NodeT* addNodeT(NodeT* node, char* city_name, int num_steps, int num_firsts) {
    // Find the correct position to addNodeT the node and addNodeT it
    if (node == NULL)
        return newNodeT(city_name, num_steps, num_firsts);
    if (num_steps < node->key)
        node->left = addNodeT(node->left, city_name, num_steps, num_firsts);
    else if (num_steps > node->key)
        node->right = addNodeT(node->right, city_name, num_steps, num_firsts);
    else return node;

    // Balance the tree
    node->height = heightT(node);

    int balance = balanceT(node);

    if (balance < -1 && num_steps < node->left->key)
        return rightRotateT(node);

    if (balance > 1 && num_steps > node->right->key)
        return leftRotateT(node);

    if (balance < -1 && num_steps > node->left->key)
        return doubleRightRotateT(node);

    if (balance > 1 && num_steps < node->right->key)
        return doubleLeftRotateT(node);

    return node;
}

