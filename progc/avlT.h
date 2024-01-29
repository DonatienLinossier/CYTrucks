#ifndef AVLT_H
#define AVLT_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodeT{//Declares the NodeT structure used for AVL trees
    int key;
    struct nodeT* left;
    struct nodeT* right;
    char* city;
    int num_firsts;
    int height;
}NodeT;

NodeT* newNodeT(char* city_name, int num_steps, int firsts){//Creates a new NodeT with the city_name as a key
    NodeT* n = malloc(sizeof(NodeT));
    n->key=num_steps;
    n->left = n->right = NULL;
    n->city = city_name;
    n->num_firsts = firsts;
    n->height=0;
    return n;
}


void inOrderT(NodeT* n){//Displays the values in the AVL tree in ascending order
    printf("n0\n");
    if(n==NULL){
        printf("n1\n");
        return;
    }
    inOrderT(n->left);
    printf("City:%s Steps:%d Firsts:%d\n",n->city,n->key,n->num_firsts);
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
        return(0);
    }

    else{
        return(heightT(n->right)-heightT(n->left));
    }
}

int getMinT(NodeT* n){
    if(n==NULL){
        exit(1);
    }
    if(n->left==NULL){
        return n->key;
    }
    return getMinT(n->left);
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

NodeT* addNodeT(NodeT* node, char* city_name, int num_steps, int num_firsts){
/* 1.  Perform the normal BST insertion */
    if (node == NULL)
        printf("z1\n");
        return(newNodeT(city_name, num_steps, num_firsts)); 
  
    if (num_steps < node->key){
        printf("z2\n");
        node->left  = addNodeT(node->left, city_name, num_steps, num_firsts);
    } 
    else if (num_steps > node->key){
        printf("z3\n");
        node->right = addNodeT(node->right, city_name, num_steps, num_firsts); 
    }
    else{ // Equal keys are not allowed in BST 
        printf("z4\n");
        return node;
    }
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + fmax(node->left->height, node->right->height); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = balanceT(node);
    printf("z5\n");
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && num_steps < node->left->key){
        printf("z6\n");
        return rightRotateT(node); 
    }
  
    // Right Right Case 
    if (balance < -1 && num_steps > node->right->key){
        printf("z7\n");
        return leftRotateT(node);
    }
  
    // Left Right Case 
    if (balance > 1 && num_steps > node->left->key) 
    { 
        printf("z8\n");
        return doubleRightRotateT(node);
    } 
  
    // Right Left Case 
    if (balance < -1 && num_steps < node->right->key) 
    { 
        printf("z9\n");
        return doubleLeftRotateT(node);
    } 
  
    /* return the (unchanged) node pointer */
    printf("z10\n");
    return node; 
}
#endif //PROCESST_H