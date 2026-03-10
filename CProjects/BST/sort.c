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
    printf("Node_value: %d\n", t->value);
    printAll(t->right);
}

void removeAll(Tree t) {
    if (t == NULL)
        return;
    removeAll(t->left);
    removeAll(t->right);
    free(t);
}

int removeMinRec(Tree *treePtr, Tree *parent) {
    assert((*treePtr) != NULL);
    Tree *left = &((*treePtr)->left);
    if (*left != NULL) {
        return removeMinRec(left, treePtr);
    }
    else {
        int result = (*treePtr)->value;
        Tree *right = &((*treePtr)->right);
        if (*right != NULL && parent != NULL) {
            (*parent)->left = *right;
        }
        else if (parent != NULL) {
            (*parent) -> left = NULL;
        }
        free(*treePtr);
        return result;
    }
}

int removeMin(Tree *treePtr) {
    return removeMinRec(treePtr, NULL);
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
    printf("Deleted: %d\n",removeMin(&treePtr));
    printAll(treePtr);
    removeAll(treePtr);
    return 0;
}