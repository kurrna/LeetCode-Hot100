//
// Created by Kurna on 25-7-13.
//
#include <stdio.h>
#include <stdlib.h>
#include <tree.h>

struct TreeNode *invertTree(struct TreeNode *root) {
    return NULL;
}

void test_invertTree() {
    int arr[] = {4, 2, 7, 1, 3, 6, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = buildBinaryTree(arr, size, 0);
    struct TreeNode *ret = invertTree(root);
}
