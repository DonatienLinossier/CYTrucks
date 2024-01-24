#ifndef AVLS_H
#define AVLS_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct nodeS{//Declares the nodeS structure used for AVL trees
    int key;
    struct nodeS* left;
    struct nodeS* right;
    int min,max,total,num_steps,height;
}NodeS;

NodeS* newNodeS(int route_id, int distance){//Creates a new NodeS with "a" as a key
    NodeS* n = malloc(sizeof(NodeS));
    n->key=route_id;
    n->left = n->right = NULL;
    n->min = n->max = n->total = distance;
    n->num_steps=1;
    n->height=0;
    return n;
}

void printNodeS(NodeS* n){
    if(n==NULL){
        printf("NULL\n");
    }
    printf("Routeid=%d min=%d max=%d total=%d num_steps=%d\n",n->key,n->min,n->max,n->total,n->num_steps);
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
        return(0);
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

NodeS* addNodeS(NodeS* node, int route_id, int distance){
/* 1.  Perform the normal BST insertion */
    if (node == NULL)
        printf("z1\n");
        return(newNodeS(route_id, distance)); 
  
    if (route_id < node->key){
        printf("z2\n");
        node->left  = addNodeS(node->left, route_id, distance);
    } 
    else if (route_id > node->key){
        printf("z3\n");
        node->right = addNodeS(node->right, route_id, distance); 
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
    int balance = balanceS(node);
    printf("z5\n");
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // Left Left Case 
    if (balance > 1 && route_id < node->left->key){
        printf("z6\n");
        return rightRotateS(node); 
    }
  
    // Right Right Case 
    if (balance < -1 && route_id > node->right->key){
        printf("z7\n");
        return leftRotateS(node);
    }
  
    // Left Right Case 
    if (balance > 1 && route_id > node->left->key) 
    { 
        printf("z8\n");
        return doubleRightRotateS(node);
    } 
  
    // Right Left Case 
    if (balance < -1 && route_id < node->right->key) 
    { 
        printf("z9\n");
        return doubleLeftRotateS(node);
    } 
  
    /* return the (unchanged) node pointer */
    printf("z10\n");
    return node; 
}


// Function to perform in-order traversal and find the nodes with the highest differences between min and max
void getMaxRangeValues(NodeS* root, int* count, NodeS* maxRangeNodes[], int maxRangeValues[]) {
    if (root != NULL) {
        printf("g1\n");
        // Traverse the right subtree first
        getMaxRangeValues(root->right, count, maxRangeNodes, maxRangeValues);
        printf("g2\n");
        if ((root->max-root->min) > maxRangeValues[49]) {
            // Insert the current node into the top 50
            int i = *count;
            printf("g3\n");
            while (i > 0 && (i >= 50 || (root->max-root->min) > maxRangeValues[i - 1])) {
                printf("g4\n");
                
                maxRangeValues[i] = maxRangeValues[i - 1];
                printf("%d\n",*count);
                printf("f\n");
                maxRangeNodes[i] = maxRangeNodes[i - 1];
                i--;
            }
            printf("g5\n");
            maxRangeValues[i] = (root->max-root->min);
            maxRangeNodes[i] = root;

            // Update the count
            printf("%d\n",*count);
            (*count)++;
            printf("g6\n");
        }
        printf("g7\n");
        // Traverse the left subtree
        getMaxRangeValues(root->left, count, maxRangeNodes, maxRangeValues);
        printf("g8\n");
    }
}



#endif //AVLS_H