#include "avl.h"

int main(){
    Node* n = newNode(1);
    n=addNode(n, 3);
    n=addNode(n, 6);
    printf("%d %d \n",height(n),balance(n));
    inOrder(n);
    return 0;
}