//
// Created by Kurna on 25-7-3.
//
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}


void inorder(struct TreeNode *root, int *ret, int *retSize) {
    if (!root) return;
    inorder(root->left, ret, retSize);
    ret[(*retSize)++] = root->val;
    inorder(root->right, ret, retSize);
}

int *inorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    int *ret = malloc(sizeof(int) * 501);
    if (ret == NULL) exit(1);
    inorder(root, ret, returnSize);
    return ret;
}

void test() {
    struct TreeNode *root = createNode(1);
    root->right = createNode(2);
    root->right->left = createNode(3);
    int *returnSize = malloc(sizeof(int));
    if (returnSize == NULL) exit(1);
    int *ret = inorderTraversal(root, returnSize);
    printf("[");
    for (int i = 0; i < *returnSize; i++) {
        printf("%d", *ret+i);
        if (i == *returnSize - 1) printf("]");
        else printf(",");
    }
}