//
// Created by Kurna on 25-7-25.
//
#include <cassert>
#include <tree.hpp>
#include <iostream>

class Solution {
private:
    void dfs(TreeNode *node, int sum, int last) {
        if (node == nullptr) return;
        if (node->left) {
        }
    }
public:
    int pathSum(TreeNode *root, int targetSum) {

    }

};

int main() {
    Solution sol;
    const std::vector arr = {10, 5, -3, 3, 2, -1, 11, 3, -2, -1, 1};
    constexpr int targetSum = 8;
    TreeNode *root = TreeUtils::arrToTree(arr);
    assert(sol.pathSum(root, targetSum), 3);
    TreeUtils::freeTree(root);
    return 0;
}