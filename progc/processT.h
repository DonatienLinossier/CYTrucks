#ifndef PROCESST_H
#define PROCESST_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodeT{//Declares the NodeT structure used for AVL trees
    char* key;
    int balance;
    struct nodeT* left;
    struct nodeT* right;
    int num_step;
    struct nodeT* drivers;
}NodeT;

NodeT* newNodeT(char* a){//Creates a new NodeT with "a" as a key
    NodeT* n = malloc(sizeof(NodeT));
    n->key=a;
    n->left = n->right = n->drivers = NULL;
    n->num_step=0;
    return n;
}


void inOrderT(NodeT* n){//Displays the values in the AVL tree in ascending order
    if(n==NULL){
        return;
    }
    inOrderT(n->left);
    printf("%s\n",n->key);
    inOrderT(n->right);
    return;
}

int heightT(NodeT* n){//Returns the height of the AVL tree(Max number of sons)
    if(n->right == NULL && n->left == NULL){
        return 1;
    }
    else if(n->right == NULL){
        return 1+heightT(n->left);
    }
    else if(n->left == NULL){
        return 1+heightT(n->right);
    }
    else{
        return 1+fmax(heightT(n->left),heightT(n->right));
    }
}

int balanceT(NodeT* n){//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)
    if(n==NULL){
        exit(1);
    }
    if(n->right == NULL && n->left == NULL){
        return 0;
    }
    else if(n->right == NULL){
        return -heightT(n->left);
    }
    else if(n->left == NULL){
        return heightT(n->right);
    }
    else{
        return(heightT(n->right)-heightT(n->left));
    }
}

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeTs

NodeT* rightRotateT(NodeT* n){//To use when the right branch is too heavy and straight
    NodeT* u = n->left;
    n->left = u->right;
    u->right = n;
    return u;
}

NodeT* leftRotateT(NodeT* n){//To use when the left branch is too heavy and straight
    NodeT* u = n->right;
    n->right = u->left;
    u->left = n;
    return u;
}

NodeT* doubleLeftRotateT(NodeT* n){//To use when the right branch is too heavy and is bended
    n->right = rightRotateT(n->right);
    return leftRotateT(n);
}

NodeT* doubleRightRotateT(NodeT* n){//To use when the left branch is too heavy and is bended
    n->left = leftRotateT(n->left);
    return rightRotateT(n);
}

NodeT* addStepT(NodeT* n, char* city, char* name){//Adds a NodeT of key v to the AVL Tree, then fixes the balance of the tree using rotations if needed
    if (n==NULL){
        NodeT * new_node=newNodeT(city);
        new_node = addStepT(new_node, name, NULL);
        return new_node;
    }
    int str_comp=strcmp(city, n->key);

    if(str_comp==0){
        n->drivers = addStepT(n->drivers, name, NULL);
    }

    else if (str_comp<0){
        n->left = addStepT(n->left, city, name);
    
        if(balanceT(n)<=-2){
            if(strcmp(city, n->left->key) < 0){
                
                n = rightRotateT(n);
            }
            else {
                n = doubleRightRotateT(n);
            }
        }
    }
    else if (str_comp>0){
        n->right = addStepT(n->right, city, name);
        if(balanceT(n)>=2){
            if(strcmp(city, n->right->key) > 0){
                n = leftRotateT(n);
            }
            else {
                n = doubleLeftRotateT(n);
            }
        }
    }
    return n;
}

#endif //PROCESST_H