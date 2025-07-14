//
// Created by Kurna on 25-7-15.
//
#include <stdbool.h>
#include <stdio.h>
#include <tree.h>

// recursion
bool isSameTree(struct TreeNode *p, struct TreeNode *q) {
    if (p == NULL || q == NULL) {
        return p == q;
    }
    return p->val == q->val && isSameTree(p->left, q->right) && isSameTree(p->right, q->left);
}

bool isSymmetric(struct TreeNode *root) {
    if (root == NULL) return true;
    return isSameTree(root->left, root->right);
}

// iteration

void test() {
    int arr[] = {1, 2, 2, 3, 4, 4, 3};
    struct TreeNode *root = buildBinaryTree(arr, sizeof(arr) / sizeof(arr[0]), 0);
    printf("%d", isSymmetric(root));
}