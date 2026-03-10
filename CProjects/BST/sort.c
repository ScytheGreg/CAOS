#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Tree;
struct Node {
    int value;
    Tree left;
    Tree right;
};


void setRight_(const Tree *treePtr, Tree child) {
    assert(treePtr && *treePtr);
    (*treePtr) -> right = child;
}

void setRight(const Tree *treePtr, const Tree *child) {
    if (treePtr && *treePtr) {
        if (child)
            setRight_(treePtr, *child);
        else
            setRight_(treePtr, NULL);
    }
}

void setLeft_(const Tree *treePtr, Tree child) {
    assert(treePtr && *treePtr);
    (*treePtr) -> left = child;
}

void setLeft(const Tree *treePtr, const Tree *child) {
    if (treePtr && *treePtr) {
        if (child)
            setLeft_(treePtr, *child);
        else
            setLeft_(treePtr, NULL);
    }
}

void setValue(const Tree *treePtr, int value) {
    assert(treePtr && *treePtr);
    (*treePtr) -> value = value;
}

int getValue(const Tree *treePtr) {
    assert(treePtr && *treePtr);
    return (*treePtr) -> value;
}

Tree *getRight(const Tree *treePtr) {
    if(!treePtr || !*treePtr)
        return NULL;
    return &((*treePtr) -> right);
}

Tree *getLeft(const Tree *treePtr) {
    if ((!treePtr || !*treePtr))
        return NULL;
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

Tree *nextBranch(const Tree *treePtr, int value) {
    assert(treePtr && *treePtr);
    assert(getValue(treePtr) != value);
    if (getValue(treePtr) > value)
        return getLeft(treePtr);
    return getRight(treePtr);
}

void insert(const Tree* treePtr, int value) {
    assert(treePtr);
    Tree branch = *treePtr;
    Tree *brPtr = &branch;
    while (branch) {
        if (getValue(brPtr) == value)
            return;
        brPtr = nextBranch(brPtr, value);
    }
    allocNode(brPtr, value);
}

void printAll(const Tree *treePtr) {
    if (treePtr && *treePtr) {
        printAll(getLeft(treePtr));
        printf("Node_value: %d\n", getValue(treePtr));
        printAll(getRight(treePtr));
    }
}

void deleteNode(const Tree* treePtr) { }

void removeAll(const Tree* treePtr) {
    if (treePtr && *treePtr) {
        removeAll(getRight(treePtr));
        removeAll(getLeft(treePtr));
        free(*treePtr);
    }
}

void changeRoot(Tree *treePtr, Tree* newRoot) {
    if (treePtr && *treePtr) {
        if (!newRoot) {
            *treePtr = NULL;
        }
        else {
            *treePtr = *newRoot;
        }
    }
}

int removeMin(Tree *treePtr) {
    assert(treePtr && *treePtr);
    int result = getValue(treePtr);
    if (!getLeft(treePtr)) {
        changeRoot(treePtr, getRight(treePtr));
    }
    else {
        Tree branch = *treePtr;
        Tree *brPtr = &branch;
        while (getLeft(getLeft(brPtr))) {
            brPtr = getLeft(brPtr);
        }
        setLeft(brPtr, getLeft(getRight(brPtr)));
    }
    free(*treePtr);
    return result;
}

// To be written
void removeValue(Tree* treePtr, int value) {
    if (treePtr && *treePtr) {

        if (!getRight(treePtr))
            changeRoot(treePtr, getLeft(treePtr));
        else {
            Tree *brPtr = getRight(treePtr); // Take the smallest value from right subforest
            while (getLeft(brPtr)) {
                brPtr = getLeft(brPtr);
            }
        }

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