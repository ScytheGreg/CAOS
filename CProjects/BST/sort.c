#include <stdio.h>
#include  <stdlib.h>
#include  <assert.h>

typedef struct Node* Tree;
struct Node {
    int value;
    Tree left;
    Tree right;
};

void insert(Tree *treePtr, int x) {
    if ((*treePtr) == NULL) {
        (*treePtr) = (Tree) malloc(sizeof(struct Node));
        assert((*treePtr) != NULL);
        (*treePtr) -> value = x;
        (*treePtr) -> left = NULL;
        (*treePtr) -> right = NULL;
    }
    else {
        if ((*treePtr) -> value > x) {
            insert(&((*treePtr)->left), x);
        }
        else if ((*treePtr) -> value < x) {
            insert(&((*treePtr)->right), x);
        }
    }
}

void printAll(Tree t) {
    if (t == NULL)
        return;
    printAll(t->left);
    printf("%d\n", t->value);
    printAll(t->right);
}

void removeAll(Tree t) {
    if (t == NULL)
        return;
    removeAll(t->left);
    removeAll(t->right);
    free(t);
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
    printAll(treePtr);
    removeAll(treePtr);
    return 0;
}