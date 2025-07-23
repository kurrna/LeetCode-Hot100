//
// Created by Kurna on 25-7-9.
//

#ifndef TREE_H
#define TREE_H

#pragma once
#include <stdlib.h>
#include <math.h>

struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

static inline struct TreeNode *createNode(const int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static inline struct TreeNode *arrToTree(int arr[], int size, int i) {
    if (i >= size || arr[i] == -1) {
        return NULL;
    }
    struct TreeNode *node = createNode(arr[i]);
    node->left = arrToTree(arr, size, 2 * i + 1);
    node->right = arrToTree(arr, size, 2 * i + 2);
    return node;
}

static inline int *treeToArr(struct TreeNode *root, int *returnSize) {
    struct TreeNode **queue = malloc(sizeof(struct TreeNode *) * 10);
    int *ret = malloc(sizeof(int) * 100);
    *returnSize = 0;
    int head = 0, tail = -1, size = 0;
    tail = (tail + 1) % 9, size++;
    queue[tail] = root;
    struct TreeNode *tempNode = malloc(sizeof(struct TreeNode));
    while (size > 0) {
        tempNode = queue[head];
        head = (head + 1) % 9, size--;
        ret[(*returnSize)++] = tempNode->val;
        if (tempNode->left) {
            tail = (tail + 1) % 9, size++;
            queue[tail] = tempNode->left;
        }
        if (tempNode->right) {
            tail = (tail + 1) % 9, size++;
            queue[tail] = tempNode->right;
        }
    }
    free(tempNode);
    free(queue);
    return ret;
}

#endif //TREE_H
