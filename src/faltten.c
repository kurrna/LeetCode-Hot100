//
// Created by Kurna on 25-7-23.
//
#include <stdio.h>
#include <stdlib.h>
#include <tree.h>

void preOrder(struct TreeNode *node, struct TreeNode **ret, int *pos) {
    if (!node) return;
    ret[(*pos)++] = node;
    preOrder(node->left, ret, pos);
    preOrder(node->right, ret, pos);
}

void flatten(struct TreeNode *root) {
    struct TreeNode **ret = malloc(sizeof(struct TreeNode *) * 2000);
    int *pos = malloc(sizeof(int));
    if (!ret || !pos) exit(1);
    *pos = 0;
    preOrder(root, ret, pos);
    for (int i = 0; i < *pos - 1; i++) {
        struct TreeNode *temp = ret[i];
        temp->right = ret[i + 1];
        temp->left = NULL;
    }
}

void test() {
    int arr[] = {1, 2, 5, 3, 4, -1, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = arrToTree(arr, size, 0);
    flatten(root);
    int *returnSize = malloc(sizeof(int));
    int *ret = treeToArr(root, returnSize);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        printf("%d", ret[i]);
        if (i != *returnSize - 1) printf(",");
    }
    printf("]");
    free(returnSize);
    free(ret);
}
