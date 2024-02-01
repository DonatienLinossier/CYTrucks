#ifndef AVLS_H
#define AVLS_H

typedef struct nodeS{//Declares the nodeS structure used for AVL trees
    int key;
    struct nodeS* left;
    struct nodeS* right;
    float min,max,total;
    int num_steps,height;
}NodeS;

NodeS* newNodeS(int route_id, float distance);//Creates a new NodeS with "a" as a key

void printNodeS(NodeS* n);

void inOrderS(NodeS* n);//Displays the values in the AVL tree in ascending order

int heightS(NodeS* n);//Returns the height of the AVL tree(Max number of sons)

int balanceS(NodeS* n);//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeSs
NodeS* rightRotateS(NodeS* y);//To use when the right branch is too heavy and straight

NodeS* leftRotateS(NodeS* x);//To use when the left branch is too heavy and straight

NodeS* addNodeS(NodeS* node, int route_id, float distance);// Find the correct position to addNodeS the node and addNodeS it

int compareRanges(const void* c, const void* d);

void findRanges(NodeS* root, NodeS** maxRanges, int* count);

void findRangesIterative(NodeS* root, NodeS** maxRanges, int* count);

NodeS** getMaxRanges(NodeS* root, int* count);

#endif //AVLS_H