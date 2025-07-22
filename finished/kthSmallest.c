//
// Created by Kurna on 25-7-21.
//
#include <../include/tree.h>
#include <stdio.h>

void dfs(struct TreeNode *node, int *ret, int *pos, int k) {
    if (*pos == -1) return;
    if (!node) return;
    dfs(node->left, ret, pos, k);
    if (*pos == -1) return;
    if (*pos == k) {
        *ret = node->val;
        *pos = -1;
        return;
    }
    (*pos)++;
    dfs(node->right, ret, pos, k);
}

int getTreeSize(struct TreeNode *root) {
    if (!root) return 0;
    return getTreeSize(root->left) + 1 + getTreeSize(root->right);
}

int kthSmallest(struct TreeNode *root, int k) {
    int size = getTreeSize(root);
    if (size == 1) return root->val;
    int *ret = malloc(sizeof(int));
    int *pos = malloc(sizeof(int));
    if (!ret || !pos) exit(1);
    *pos = 1;
    dfs(root, ret, pos, k);
    free(pos);
    return *ret;
}

void test() {
    int arr[] = {3, 2, 4, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("kth smallest node of the tree: %d", kthSmallest(arrToTree(arr, size, 0), 1));
}
