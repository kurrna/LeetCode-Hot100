//
// Created by Kurna on 25-7-15.
//
#include <stdio.h>
#include <tree.h>

int dfs(struct TreeNode* root, int* maxDiam) {
    if (root == NULL) return 0;
    int leftMax = dfs(root->left, maxDiam);
    int rightMax = dfs(root->right, maxDiam);
    int curr = leftMax + rightMax;
    if (curr > *maxDiam) {
        *maxDiam = curr;
    }
    return fmax(leftMax, rightMax) + 1;
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int maxDiam = 0;
    dfs(root, &maxDiam);
    return maxDiam;
}

void test() {
    int arr[] = {1, 2};
    struct TreeNode *root = arrToTree(arr, sizeof(arr) / sizeof(arr[0]), 0);
    int diameter = diameterOfBinaryTree(root);
    printf("%d", diameter);
}
