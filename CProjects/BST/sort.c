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

void insert(Tree* treePtr, int value) {
    assert(treePtr);
    Tree *brPtr = treePtr;
    while (*brPtr) {
        if (getValue(brPtr) == value)
            return;
        brPtr = nextBranch(brPtr, value);
    }
    allocNode(brPtr, value);
}

void printAll(const Tree *treePtr) {
    if (treePtr && *treePtr) {
        printAll(getLeft(treePtr));
        printf("%d\n", getValue(treePtr));
        printAll(getRight(treePtr));
    }
}

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

Tree *findMin(Tree* treePtr) {
    if (treePtr && *treePtr) {
        Tree *brPtr = treePtr;
        while (getLeft(brPtr) && *getLeft(brPtr)) {
            brPtr = getLeft(brPtr);
        }
        return brPtr;
    }
    return NULL;
}

Tree *findValue(Tree* treePtr, int value) {
    if (treePtr && *treePtr) {
        Tree *brPtr = treePtr;
        while (brPtr && *brPtr && getValue(brPtr) != value)
            brPtr = nextBranch(brPtr, value);
        if (brPtr && *brPtr && getValue(brPtr) == value)
            return brPtr;
    }
    return NULL;
}

void removeRoot(Tree* treePtr) {
    if (treePtr && *treePtr) {
        Tree deleteThis = *treePtr;
        if (!getRight(treePtr) || !*getRight(treePtr)) {
            changeRoot(treePtr, getLeft(treePtr));
        }
        else {
            Tree *rightMin = findMin(getRight(treePtr));
            setLeft(rightMin, getLeft(treePtr));
            changeRoot(treePtr, getRight(treePtr));
        }
        free(deleteThis);
    }
}

int removeMin(Tree *treePtr) {
    assert (treePtr && *treePtr);
    Tree* minPtr = findMin(treePtr);
    assert (minPtr && *minPtr);
    int result = getValue(minPtr);
    removeRoot(minPtr);
    return result;
}

void removeValue(Tree* treePtr, int value) {
    if (treePtr && *treePtr) {
        Tree *valuePtr = findValue(treePtr, value);
        if (valuePtr && *valuePtr) {
            removeRoot(valuePtr);
        }
    }
}

int readInt() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("Error reading number\n");
        exit(1);
    }
    return n;
}

int main() {
    int n = readInt();
    Tree tree = NULL;
    Tree *treePtr = &tree;
    for (int i = 0; i < n; i++) {
        int x = readInt();
        if (x > 0)
            insert(treePtr, x);
        if (x < 0)
            removeValue(treePtr, -1 * x);
    }
    printAll(treePtr);
    removeAll(treePtr);
    return 0;
}