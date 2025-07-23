//
// Created by Kurna on 25-7-21.
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <tree.h>
#include <limits.h>

// recursion
// bool isValidBSTHelper(struct TreeNode *node, long long min, long long max) {
//     if (!node) return true;
//     if (node->val <= min || node->val >= max) {
//         return false;
//     }
//     return isValidBSTHelper(node->left, min, node->val) && isValidBSTHelper(node->right, node->val, max);
// }
//
// bool isValidBST(struct TreeNode *root) {
//     return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
// }

// 中序遍历BST
void inorderTraverse(struct TreeNode *node, int *ret, int *pos) {
    if (!node) return;
    inorderTraverse(node->left, ret, pos);
    ret[(*pos)++] = node->val;
    inorderTraverse(node->right, ret, pos);
}

int getTreeSize(struct TreeNode *root) {
    if (!root) return 0;
    return getTreeSize(root->left) + 1 + getTreeSize(root->right);
}

bool isValidBST(struct TreeNode *root) {
    int size = getTreeSize(root);
    if (size == 1) return true;
    int *ret = malloc(sizeof(int) * size);
    int *pos = malloc(sizeof(int));
    if (!ret || !pos) exit(1);
    *pos = 0;
    inorderTraverse(root, ret, pos);
    for (int i = 0; i < size - 1; i++) {
        if (ret[i] >= ret[i+1]) return false;
    }
    free(ret);
    free(pos);
    return true;
}

void test() {
    int arr[] = {5, 4, 6, -1, -1, 3, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct TreeNode *root = createNode(0);
    root->left = createNode(-1);
    printf("%d", isValidBST(arrToTree(arr, size, 0)));
}
