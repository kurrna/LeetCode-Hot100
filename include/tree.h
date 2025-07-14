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

static inline struct TreeNode *buildBinaryTree(int arr[], int size, int i) {
    if (i >= size || arr[i] == -1) {
        return NULL;
    }
    struct TreeNode *node = createNode(arr[i]);
    node->left = buildBinaryTree(arr, size, 2 * i + 1);
    node->right = buildBinaryTree(arr, size, 2 * i + 2);
    return node;
}

#endif //TREE_H
