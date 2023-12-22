#ifndef AVLS_H
#define AVLS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct nodeS{//Declares the nodeS structure used for AVL trees
    int key;
    struct nodeS* left;
    struct nodeS* right;
    int min,max,total,num_steps;
}NodeS;

NodeS* newNodeS(int route_id, int distance){//Creates a new NodeS with "a" as a key
    NodeS* n = malloc(sizeof(NodeS));
    n->key=route_id;
    n->left = n->right = NULL;
    n->min = n->max = n->total = distance;
    n->num_steps=1;
    return n;
}


void inOrderS(NodeS* n){//Displays the values in the AVL tree in ascending order
    if(n==NULL){
        return;
    }
    inOrderS(n->left);
    printf("%d\n",n->key);
    inOrderS(n->right);
    return;
}

int heightS(NodeS* n){//Returns the height of the AVL tree(Max number of sons)
    if(n->right == NULL && n->left == NULL){
        return 1;
    }
    else if(n->right == NULL){
        return 1+heightS(n->left);
    }
    else if(n->left == NULL){
        return 1+heightS(n->right);
    }
    else{
        return 1+fmax(heightS(n->left),heightS(n->right));
    }
}

int balanceS(NodeS* n){//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)
    if(n==NULL){
        exit(1);
    }
    if(n->right == NULL && n->left == NULL){
        return 0;
    }
    else if(n->right == NULL){
        return -heightS(n->left);
    }
    else if(n->left == NULL){
        return heightS(n->right);
    }
    else{
        return(heightS(n->right)-heightS(n->left));
    }
}

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeSs

NodeS* rightRotateS(NodeS* n){//To use when the right branch is too heavy and straight
    NodeS* u = n->left;
    n->left = u->right;
    u->right = n;
    return u;
}

NodeS* leftRotateS(NodeS* n){//To use when the left branch is too heavy and straight
    NodeS* u = n->right;
    n->right = u->left;
    u->left = n;
    return u;
}

NodeS* doubleLeftRotateS(NodeS* n){//To use when the right branch is too heavy and is bended
    n->right = rightRotateS(n->right);
    return leftRotateS(n);
}

NodeS* doubleRightRotateS(NodeS* n){//To use when the left branch is too heavy and is bended
    n->left = leftRotateS(n->left);
    return rightRotateS(n);
}

NodeS* addNodeS(NodeS* n, int route_id, int distance){//Adds a NodeS of key v to the AVL Tree, then fixes the balance of the tree using rotations if needed
    if (n==NULL){
        NodeS * new_node=newNodeS(route_id, distance);
        return new_node;
    }
    if (route_id < n->key){
        n->left = addNodeS(n->left, route_id, distance);
    
        if(balanceS(n)<=-2){
            if(route_id < n->left->key){
                n = rightRotateS(n);
            }
            else {
                n = doubleRightRotateS(n);
            }
        }
    }
    else if (route_id > n->key){
        n->right = addNodeS(n->right, route_id, distance);
        if(balanceS(n)>=2){
            if(route_id > n->right->key){
                n = leftRotateS(n);
            }
            else {
                n = doubleLeftRotateS(n);
            }
        }
    }
    else{
        n->num_steps+=1;
        n->total+=distance;
        if(distance < n->min){
            n->min=distance;
        }
        else if(distance > n->max){
            n->max = distance;
        }
    }
    return n;
}

#endif //AVLS_H