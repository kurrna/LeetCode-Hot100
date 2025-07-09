//
// Created by Kurna on 25-7-8.
//
#include <stdio.h>
#include <stdlib.h>
#include <../include/tree.h>

struct TreeNode *createNode(int val);

#define max(a, b) (a > b ? a : b)


struct QueueNode {
    struct TreeNode *p;
    struct QueueNode *next;
};

void init(struct QueueNode **p, struct TreeNode *t) {
    *p = (struct QueueNode *) malloc(sizeof(struct QueueNode));
    (*p)->p = t;
    (*p)->next = NULL;
}

int maxDepth(struct TreeNode *root) {
    if (root == NULL) return 0;
    struct QueueNode *left, *right;
    init(&left, root);
    right = left;
    int ans = 0, sz = 1, tmp = 0;
    while (left != NULL) {
        tmp = 0;
        while (sz > 0) {
            if (left->p->left != NULL) {
                init(&right->next, left->p->left);
                right = right->next;
                tmp++;
            }
            if (left->p->right != NULL) {
                init(&right->next, left->p->right);
                right = right->next;
                tmp++;
            }
            left = left->next;
            sz--;
        }
        sz += tmp;
        ans++;
    }
    return ans;
}

// dfs超时
int maxDepth_dfs(struct TreeNode *root) {
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
    free(root);
}