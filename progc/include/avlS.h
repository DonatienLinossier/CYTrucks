#ifndef AVLS_H
#define AVLS_H

// Structure definition for a node in the AVL tree
typedef struct nodeS {
    int key;           // Route ID
    struct nodeS* left;   // Pointer to the left child
    struct nodeS* right;  // Pointer to the right child
    float min, max;    // Minimum and maximum distances in the subtree rooted at this node
    float total;       // Total distance in the subtree rooted at this node
    int num_steps;     // Number of steps in the subtree rooted at this node
    int height;        // Height of the subtree rooted at this node
} NodeS;

// Function to create a new AVL tree node with the given route_id and distance
NodeS* newNodeS(int route_id, float distance);

// Function to print the details of a node in the AVL tree
void printNodeS(NodeS* n);

// Function to display the values in the AVL tree in ascending order
void inOrderS(NodeS* n);

// Function to calculate the height of the AVL tree
int heightS(NodeS* n);

// Function to calculate the balance of the AVL Tree
int balanceS(NodeS* n);

// Right rotation to balance the AVL Tree when the left branch is too heavy and straight
NodeS* rightRotateS(NodeS* y);

// Left rotation to balance the AVL Tree when the right branch is too heavy and straight
NodeS* leftRotateS(NodeS* x);

// Function to add a new node to the AVL Tree and balance the tree
NodeS* addNodeS(NodeS* node, int route_id, float distance);

// Comparison function for sorting nodes based on their ranges
int compareRanges(const void* c, const void* d);

// Function to find and update the 50 nodes with the largest ranges in the AVL tree
void findRanges(NodeS* root, NodeS** maxRanges, int* count);

// Iterative version of finding and updating the 50 nodes with the largest ranges in the AVL tree
void findRangesIterative(NodeS* root, NodeS** maxRanges, int* count);

// Function to get an array of pointers to the 50 nodes with the largest ranges in the AVL tree
NodeS** getMaxRanges(NodeS* root, int* count);

//Function that frees the whole tree
void freeNodeS(NodeS* node);

#endif // AVLS_H
