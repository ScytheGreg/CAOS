#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Tree;
struct Node {
    int value;
    Tree left;
    Tree right;
};


void setRight(Tree *treePtr, Tree child) {
    assert(treePtr && *treePtr);
    (*treePtr) -> right = child;
}

void setLeft(Tree *treePtr, Tree child) {
    assert(treePtr && *treePtr);
    (*treePtr) -> left = child;
}

void setValue(Tree *treePtr, int value) {
    assert(treePtr && *treePtr);
    (*treePtr) -> value = value;
}

int getValue(Tree *treePtr) {
    assert(treePtr && *treePtr);
    return (*treePtr) -> value;
}

Tree *getRight(Tree *treePtr) {
    assert(treePtr && *treePtr);
    return &((*treePtr) -> right);
}

Tree *getLeft(Tree *treePtr) {
    assert(treePtr && *treePtr);
    return &((*treePtr) -> left);
}

void allocNode(Tree* treePtr, int value) {
    assert(!*treePtr);
    Tree t = (Tree) malloc(sizeof(struct Node));
    assert(t);
    *treePtr = t;
    setValue(treePtr, value);
    setLeft(treePtr, NULL);
    setRight(treePtr, NULL);
}

void insert(Tree* treePtr, int value) {
    Tree branch = *treePtr;
    Tree *brPtr = &branch;
    while (branch) {
        if (getValue(brPtr) > value)
            brPtr = getLeft(brPtr);
        else if (getValue(brPtr) < value)
            brPtr = getRight(brPtr);
        else return;
    }
    allocNode(brPtr, value);
}

void printAll(Tree *treePtr) {
    if (treePtr && *treePtr) {
        printAll(getLeft(treePtr));
        printf("Node_value: %d\n", getValue(treePtr));
        printAll(getRight(treePtr));
    }
}

void removeAll(Tree* treePtr) {
    if (treePtr && *treePtr) {
        removeAll(getRight(treePtr));
        removeAll(getLeft(treePtr));
        free(*treePtr);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Tree tree = NULL;
    Tree *treePtr = &tree;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x > 0)
            insert(treePtr, x);
        //if (x < 0)
            //removeValue(&treePtr, -1 * x);
    }
    printAll(treePtr);
    removeAll(treePtr);
    return 0;
}