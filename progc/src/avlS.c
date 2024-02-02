#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../include/avlS.h"

#define NUM_VALUES_S 50

// Function to create a new AVL tree node with the given route_id and distance
NodeS* newNodeS(int route_id, float distance) {
    NodeS* n = malloc(sizeof(NodeS));
    n->key = route_id;
    n->left = n->right = NULL;
    n->min = n->max = n->total = distance;
    n->num_steps = 1;
    n->height = 0;
    return n;
}

// Function to print the details of a node in the AVL tree
void printNodeS(NodeS* n) {
    if (n == NULL) {
        printf("NULL\n");
    }
    printf("%d;%f;%f;%f;%f\n",n->key, n->min, n->total / n->num_steps, n->max, n->max - n->min);
}


// Function to display the values in the AVL tree in ascending order
void inOrderS(NodeS* n) {
    if (n == NULL) {
        return;
    }
    inOrderS(n->left);
    printf("%d\n", n->key);
    inOrderS(n->right);
}

// Function to calculate the height of the AVL tree
int heightS(NodeS* n) {
    if (n == NULL) {
        return 0;
    } else if (n->right == NULL && n->left == NULL) {
        return 1;
    } else if (n->right == NULL) {
        return 1 + n->left->height;
    } else if (n->left == NULL) {
        return 1 + n->right->height;
    } else {
        return 1 + fmax(n->left->height, n->right->height);
    }
}

// Function to calculate the balance of the AVL Tree
int balanceS(NodeS* n){
    if(n==NULL){
        return(0);
    }

    else{
        return (heightS(n->right)-heightS(n->left));
    }
}

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeSs

// Right rotation to balance the AVL Tree when the left branch is too heavy and straight
NodeS* rightRotateS(NodeS* y) {
    NodeS* x = y->left;
    NodeS* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = heightS(y);
    x->height = heightS(x);

    return x;
}

// Left rotation to balance the AVL Tree when the right branch is too heavy and straight
NodeS* leftRotateS(NodeS* x) {
    NodeS* y = x->right;
    NodeS* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = heightS(x);
    y->height = heightS(y);

    return y;
}

// Function to add a new node to the AVL Tree and balance the tree
NodeS* addNodeS(NodeS* node, int route_id, float distance) {
    // Find the correct position to add the node and add it
    if (node == NULL) {
        return newNodeS(route_id, distance);
    }
    if (route_id < node->key) {
        node->left = addNodeS(node->left, route_id, distance);
    } else if (route_id > node->key) {
        node->right = addNodeS(node->right, route_id, distance);
    } else {
        // Update values if the node with the same key already exists
        if (distance < node->min) node->min = distance;
        else if (distance > node->max) node->max = distance;
        node->total += distance;
        node->num_steps += 1;
        return node;
    }

    // Balance the tree
    node->height = heightS(node);

    int balance = balanceS(node);

    if (balance < -1 && route_id < node->left->key) {
        return rightRotateS(node);
    }

    if (balance > 1 && route_id > node->right->key) {
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

    return node;
}



// Comparison function for sorting nodes based on their ranges
int compareRanges(const void* c, const void* d) {
    const NodeS* a = *(const NodeS **)c;
    const NodeS* b = *(const NodeS **)d;
    return b->max - b->min - (a->max - a->min);
}

// Function to find and update the 50 nodes with the largest ranges in the AVL tree
void findRanges(NodeS* root, NodeS** maxRanges, int* count) {
    if (root != NULL) {
        findRanges(root->left, maxRanges, count);

        // Update maxRanges array with the current node
        if (*count < NUM_VALUES_S) {
            maxRanges[*count] = root;
            (*count)++;
        } else {
            // Check if the current node has a higher range than the lowest range in maxRanges
            if ((root->max - root->min) > (maxRanges[49]->max - maxRanges[49]->min)) {
                maxRanges[NUM_VALUES_S-1] = root;
                qsort(maxRanges, NUM_VALUES_S, sizeof(NodeS*), compareRanges);
            }
        }

        findRanges(root->right, maxRanges, count);
    }
}


// Iterative version of finding and updating the 50 nodes with the largest ranges in the AVL tree
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
        if (*count < NUM_VALUES_S) {
            maxRanges[*count] = current;
            (*count)++;
        } else {
            // Check if the current node has a higher range than the lowest range in maxRanges
            if ((current->max - current->min) > (maxRanges[49]->max - maxRanges[49]->min)) {
                maxRanges[NUM_VALUES_S-1] = current;

                // Perform insertion sort for the updated element
                for (int i = NUM_VALUES_S-2; i >= 0 && (maxRanges[i]->max - maxRanges[i]->min) < (maxRanges[i + 1]->max - maxRanges[i + 1]->min); i--) {
                    NodeS* temp = maxRanges[i];
                    maxRanges[i] = maxRanges[i + 1];
                    maxRanges[i + 1] = temp;
                }
            }
        }

        current = current->right;
    }
}


// Function to get an array of pointers to the 50 nodes with the largest ranges in the AVL tree
NodeS** getMaxRanges(NodeS* root, int* count) {
    NodeS** maxRanges = (NodeS**)malloc(NUM_VALUES_S * sizeof(NodeS*));
    *count = 0;

    // Find and update the 50 nodes with the largest ranges
    //findRanges(root, maxRanges, count);
    findRangesIterative(root, maxRanges, count);

    return maxRanges;
}

//Function that frees the whole tree
void freeNodeS(NodeS* node) {
    if (node == NULL) return;
    
    freeNodeS(node->left);
    freeNodeS(node->right);
    free(node);
}
