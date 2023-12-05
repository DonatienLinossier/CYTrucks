#include <stdio.h>
#include <stdlib.h>

typedef struct node(
    int a;
    int balance;
    struct node* ls;
    struct node* rs;
)Node;

Node* newNode(int a){
    Node* n = malloc(sizeof(Node));
    n.a=a;
    return n;
}

int height(Node* n){
    if(n->rs is None and n->ls is None){
        return 0;
    }
    else if(n->rs is None){
        return 1+height(n->ls);
    }
    else if(n->ls is None){
        return 1+height(n->rs);
    }
    else{
        return 1+max(height(n->ls),height(n->rs))
    }
}

int balance(Node* n){
    if(n->rs is None and n->ls is None){
        return 0;
    }
    else if(n->rs is None){
        return -height(n->ls);
    }
    else if(n->ls is None){
        return height(n->rs);
    }
    else{
        return(height(n->rs)-height(n->rs));
    }
}

