#ifndef AVLT_H
#define AVLT_H

typedef struct nodeT{//Declares the NodeT structure used for AVL trees
    int key;
    struct nodeT* left;
    struct nodeT* right;
    char* city;
    int num_firsts;
    int height;
}NodeT;

NodeT* newNodeT(char* city_name, int num_steps, int firsts);//Creates a new NodeT with the city_name as a key

void inOrderT(NodeT* n,int* count);//Displays the values in the AVL tree in ascending order

int heightT(NodeT* n);//Returns the height of the AVL tree(Max number of sons)

int balanceT(NodeT* n);//Returns the balance of the AVL Tree(height of its right branch - height of its left branch, should be between -1 and 1)

int getMin(int values[],int length);

//Rotations are used to balance the AVL Tree when it is unbalanced by shifting the NodeTs
NodeT* rightRotateT(NodeT* y);//To use when the right branch is too heavy and straight

NodeT* leftRotateT(NodeT* x);//To use when the left branch is too heavy and straight

void freeNodeT(NodeT* node);

NodeT* addNodeT(NodeT* node, char* city_name, int num_steps, int num_firsts);


#endif //AVLT_H