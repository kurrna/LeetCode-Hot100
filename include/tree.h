//
// Created by Kurna on 25-7-9.
//

#ifndef TREE_H
#define TREE_H

#pragma once
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

inline struct TreeNode *createNode(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}


#endif //TREE_H
