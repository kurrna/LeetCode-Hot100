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
        if (arr.empty() || arr[0] == INT_MIN) return nullptr;
        auto *root = new TreeNode(arr[0]);
        std::queue<TreeNode *> q;
        q.push(root);
        int index = 1;
        while (index < arr.size() && !q.empty()) {
            TreeNode *current = q.front();
            q.pop();
            if (index < arr.size() && arr[index] != INT_MIN) {
                current->left = new TreeNode(arr[index]);
                q.push(current->left);
            }
            index++;
            if (index < arr.size() && arr[index] != INT_MIN) {
                current->right = new TreeNode(arr[index]);
                q.push(current->right);
            }
            index++;
        }
        return root;
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
};

#endif // TREE_H
