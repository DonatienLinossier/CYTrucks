#ifndef AVLT2_H
#define AVLT2_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodeT2{//Declares the NodeT structure used for AVL trees
    char* key;
    int balance;
    struct nodeT2* left;
    struct nodeT2* right;
    int num_step;
    struct nodeT2* drivers;
}NodeT2;

NodeT2* newNodeT2(char* city){//Creates a new NodeT with "a" as a key
    NodeT2* n = malloc(sizeof(NodeT2));
    n->key=city;
    n->left = n->right = n->drivers = NULL;
    n->num_step=0;
    return n;
}


void inOrderT2(NodeT2* n){//Displays the values in the AVL tree in ascending order
    if(n==NULL){
        return;
    }
    inOrderT2(n->left);
    printf("%s\n",n->key);
    inOrderT2(n->right);
    return;
}

int heightT2(NodeT2* n){//Returns the height of the AVL tree(Max number of sons)
    if(n->right == NULL && n->left == NULL){
        return 1;
    }
    else if(n->right == NULL){
        return 1+heightT2(n->left);
    }
    else if(n->left == NULL){
        return 1+heightT2(n->right);
    }
    else{
        return 1+fmax(heightT2(n->left),heightT2(n->right));
    }
}

int balanceT2(NodeT2* n){//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)
    if(n==NULL){
        exit(1);
    }
    if(n->right == NULL && n->left == NULL){
        return 0;
    }
    else if(n->right == NULL){
        return -heightT2(n->left);
    }
    else if(n->left == NULL){
        return heightT2(n->right);
    }
    else{
        return(heightT2(n->right)-heightT2(n->left));
    }
}

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeTs

NodeT2* rightRotateT2(NodeT2* n){//To use when the right branch is too heavy and straight
    NodeT2* u = n->left;
    n->left = u->right;
    u->right = n;
    return u;
}

NodeT2* leftRotateT2(NodeT2* n){//To use when the left branch is too heavy and straight
    NodeT2* u = n->right;
    n->right = u->left;
    u->left = n;
    return u;
}

NodeT2* doubleLeftRotateT2(NodeT2* n){//To use when the right branch is too heavy and is bended
    n->right = rightRotateT2(n->right);
    return leftRotateT2(n);
}

NodeT2* doubleRightRotateT2(NodeT2* n){//To use when the left branch is too heavy and is bended
    n->left = leftRotateT2(n->left);
    return rightRotateT2(n);
}

NodeT2* addStepT2(NodeT2* n, char* city, char* name){//Adds a NodeT2 of key v to the AVL Tree, then fixes the balance of the tree using rotations if needed
    if (n==NULL){
        NodeT2 * new_node=newNodeT2(city);
        new_node = addStepT2(new_node, name, NULL);
        return new_node;
    }
    int str_comp=strcmp(city, n->key);

    if(str_comp==0){
        n->drivers = addStepT2(n->drivers, name, NULL);
    }

    else if (str_comp<0){
        n->left = addStepT2(n->left, city, name);

        if(balanceT2(n)<=-2){
            if(strcmp(city, n->left->key) < 0){

                n = rightRotateT2(n);
            }
            else {
                n = doubleRightRotateT2(n);
            }
        }
    }
    else if (str_comp>0){
        n->right = addStepT2(n->right, city, name);
        if(balanceT2(n)>=2){
            if(strcmp(city, n->right->key) > 0){
                n = leftRotateT2(n);
            }
            else {
                n = doubleLeftRotateT2(n);
            }
        }
    }
    return n;
}

#endif //AVLT2_H 