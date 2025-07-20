//
// Created by Kurna on 25-7-15.
//
#include <stdbool.h>
#include <stdio.h>
#include <../include/tree.h>

// recursion
// bool isSameTree(struct TreeNode *p, struct TreeNode *q) {
//     if (p == NULL || q == NULL) {
//         return p == q;
//     }
//     return p->val == q->val && isSameTree(p->left, q->right) && isSameTree(p->right, q->left);
// }
//
// bool isSymmetric(struct TreeNode *root) {
//     if (root == NULL) return true;
//     return isSameTree(root->left, root->right);
// }

// iteration
bool check(struct TreeNode *a, struct TreeNode *b) {
    struct TreeNode **q = malloc(sizeof(struct TreeNode *) * 100);
    int head = 0, tail = -1, size = 2;
    q[++tail] = a, q[++tail] = b;
    while (size > 0) {
        a = q[head], head = (head + 1) % 99;
        b = q[head], head = (head + 1) % 99;
        size -= 2;
        if (!a && !b) continue;
        if (!a || !b || a->val != b->val) return false;
        tail = (tail + 1) % 99, q[tail] = a->left;
        tail = (tail + 1) % 99, q[tail] = b->right;
        tail = (tail + 1) % 99, q[tail] = a->right;
        tail = (tail + 1) % 99, q[tail] = b->left;
        size += 4;
    }
    free(q);
    return true;
}

bool isSymmetric(struct TreeNode *root) {
    return check(root, root);
}

void test() {
    int arr[] = {1, 2, 2, 3, 4, 4, 3};
    struct TreeNode *root = arrToTree(arr, sizeof(arr) / sizeof(arr[0]), 0);
    printf("%d", isSymmetric(root));
}
