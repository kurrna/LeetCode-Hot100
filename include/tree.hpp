//
// Created by Kurna on 25-7-25.
//

#ifndef TREE_H
#define TREE_H

#pragma once
#include <memory>
#include <vector>
#include <queue>
#include <stdexcept>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class TreeUtils {
public:
    static TreeNode *arrToTree(const std::vector<int>& arr) {
        if (arr.empty() || arr[0] == -1) return nullptr;
        return arrToTreeHelper(arr, 0);
    }

    static std::vector<int> treeToArr(const std::unique_ptr<TreeNode>& root) {
        std::vector<int> result;
        if (!root) return result;
        std::queue<const TreeNode*> q;
        q.push(root.get());
        while (!q.empty()) {
            const TreeNode* node = q.front();
            q.pop();
            result.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return result;
    }

    static void freeTree(const TreeNode *root) {
        if (root == nullptr) return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
        root = nullptr;
    }

private:
    static TreeNode *arrToTreeHelper(const std::vector<int>& arr, size_t index) {
        if (index >= arr.size() || arr[index] == -1) return nullptr;
        auto *node = new TreeNode(arr[index]);
        node->left = arrToTreeHelper(arr, 2 * index + 1);
        node->right = arrToTreeHelper(arr, 2 * index + 2);
        return node;
    }
};

#endif // TREE_H
