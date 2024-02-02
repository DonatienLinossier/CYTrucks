#ifndef AVLT_H
#define AVLT_H

// Structure for AVL tree node
typedef struct nodeT {
    int key;              // Key value for AVL tree node
    struct nodeT* left;   // Pointer to the left child
    struct nodeT* right;  // Pointer to the right child
    char* city;           // City name
    int num_firsts;       // Number of firsts
    int height;           // Height of the node in the AVL tree
} NodeT;

// Function to create a new AVL tree node with the given city_name, num_steps, and num_firsts
NodeT* newNodeT(char* city_name, int num_steps, int firsts);

// Function to print the details of a node in the AVL tree
void printNodeT(NodeT* n);

// Function to display values in the AVL tree in ascending order
void inOrderT(NodeT* n, int* count, NodeT* results[]);

// Function to return the height of the AVL tree (maximum number of sons)
int heightT(NodeT* n);

// Function to return the balance of the AVL Tree (height of its right branch - height of its left branch, should be between -1 and 1)
int balanceT(NodeT* n);

// Function to find the index of the minimum value in an array
int getMin(int values[], int length);

// Rotations are used to balance the AVL Tree when it is unbalanced by shifting the nodes

// Right rotation to use when the right branch is too heavy and straight
NodeT* rightRotateT(NodeT* y);

// Left rotation to use when the left branch is too heavy and straight
NodeT* leftRotateT(NodeT* x);

// Left then right rotate to balance the AVL Tree when the right branch is too heavy but bended
NodeT* doubleRightRotateT(NodeT* n);

// Right then left rotate to balance the AVL Tree when the left branch is too heavy but bended
NodeT* doubleLeftRotateT(NodeT* n);

// Function that frees the entire AVL tree
void freeNodeT(NodeT* node);

// Comparison function for qsort
int compareT(const void* c, const void* d);

// Function to add a new node to the AVL tree
NodeT* addNodeT(NodeT* node, char* city_name, int num_steps, int num_firsts);

#endif // AVLT_H
