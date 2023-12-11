#include "avl.h"

int main(){
    Node* n = newNode(6);
    addNode(n, 3);
    addNode(n, 1);
    printf("%d %d \n",height(n),balance(n));
    inOrder(n);
    return 0;
}