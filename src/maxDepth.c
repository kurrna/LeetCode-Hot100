//
// Created by Kurna on 25-7-8.
//
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

struct TreeNode *createNode(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(struct TreeNode *root) {

}

int maxDepth(struct TreeNode *root) {
    if (root == NULL) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

void test() {
    struct TreeNode *root = createNode(3);
    root->left = createNode(9);
    root->right = createNode(20);
    root->right->left = createNode(15);
    root->right->right = createNode(7);
    printf("%d", maxDepth(root));
    freeTree(root);
    free(root);
}