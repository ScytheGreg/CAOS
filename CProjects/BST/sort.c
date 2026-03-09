#include <stdio.h>
#include  <stdlib.h>

typedef struct Node* Tree;
struct Node {
    int value;
    Tree left;
    Tree right;
};

void insert(Tree *treePtr, int x) {
    Tree t = *treePtr;
    if (t == NULL) {
        t = (Tree) malloc(sizeof(struct Node));
        t -> value = x;
        t -> left = NULL;
        t -> right = NULL;
        treePtr = &t;
        printf("New node added\n");
    }
    else {
        if (t -> value < x) {
            insert(&(t->left), x);
        }
        else {
            insert(&(t->right), x);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Tree treePtr = NULL;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        insert(&treePtr, x);
    }
}