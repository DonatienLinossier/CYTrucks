#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../include/avlS.h"

NodeS* newNodeS(int route_id, float distance){//Creates a new NodeS with "a" as a key
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

int balanceS(NodeS* n){//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)
    if(n==NULL){
        return(0);
    }

    else{
        return (heightS(n->right)-heightS(n->left));
    }
}

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeSs

NodeS* rightRotateS(NodeS* y){//To use when the right branch is too heavy and straight
    NodeS* x = y->left;
    NodeS* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = heightS(y);
    x->height = heightS(x);

    return x;
}

NodeS* leftRotateS(NodeS* x){//To use when the left branch is too heavy and straight
    NodeS* y = x->right;
    NodeS* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = heightS(x);
    y->height = heightS(y);

    return y;
}

NodeS* addNodeS(NodeS* node, int route_id, float distance){
// Find the correct position to addNodeS the node and addNodeS it
    if (node == NULL){
        return newNodeS(route_id, distance);
    }
    if (route_id < node->key){
        node->left = addNodeS(node->left, route_id, distance);
    }
    else if (route_id > node->key){
        node->right = addNodeS(node->right, route_id, distance);
    }
    else{
        if(distance<node->min)node->min=distance;
        else if(distance>node->max)node->max=distance;
        node->total+=distance;
        node->num_steps+=1;
        return node;
    }

    // Balance the tree
    node->height = heightS(node);

    int balance = balanceS(node);

    if (balance < -1 && route_id < node->left->key){
        return rightRotateS(node);
    }

    if (balance > 1 && route_id > node->right->key){
        return leftRotateS(node);
    }

    if (balance < -1 && route_id > node->left->key) {
        node->left = leftRotateS(node->left);
        return rightRotateS(node);
    }

    if (balance > 1 && route_id < node->right->key) {
        node->right = rightRotateS(node->right);
        return leftRotateS(node);
    }

    //printf("return\n");
    return node;
}


int compareRanges(const void* c, const void* d) {
    const NodeS* a = *(const NodeS **)c;
    const NodeS* b = *(const NodeS **)d;
    return b->max - b->min - (a->max - a->min);
}

void findRanges(NodeS* root, NodeS** maxRanges, int* count) {
    if (root != NULL) {
        findRanges(root->left, maxRanges, count);

        // Update maxRanges array with the current node
        if (*count < 50) {
            maxRanges[*count] = root;
            (*count)++;
        } else {
            // Check if the current node has a higher range than the lowest range in maxRanges
            if ((root->max - root->min) > (maxRanges[49]->max - maxRanges[49]->min)) {
                maxRanges[49] = root;
                qsort(maxRanges, 50, sizeof(NodeS*), compareRanges);
            }
        }

        findRanges(root->right, maxRanges, count);
    }
}

void findRangesIterative(NodeS* root, NodeS** maxRanges, int* count) {
    NodeS* current = root;
    NodeS* stack[100]; // Adjust the size as needed
    int top = -1;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];

        // Update maxRanges array with the current node
        if (*count < 50) {
            maxRanges[*count] = current;
            (*count)++;
        } else {
            // Check if the current node has a higher range than the lowest range in maxRanges
            if ((current->max - current->min) > (maxRanges[49]->max - maxRanges[49]->min)) {
                maxRanges[49] = current;

                // Perform insertion sort for the updated element
                for (int i = 48; i >= 0 && (maxRanges[i]->max - maxRanges[i]->min) < (maxRanges[i + 1]->max - maxRanges[i + 1]->min); i--) {
                    NodeS* temp = maxRanges[i];
                    maxRanges[i] = maxRanges[i + 1];
                    maxRanges[i + 1] = temp;
                }
            }
        }

        current = current->right;
    }
}


NodeS** getMaxRanges(NodeS* root, int* count) {
    NodeS** maxRanges = (NodeS**)malloc(50 * sizeof(NodeS*));
    *count = 0;

    //findRanges(root, maxRanges, count);
    findRanges(root, maxRanges, count);

    return maxRanges;
}
