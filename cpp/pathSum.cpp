//
// Created by Kurna on 25-7-25.
//
#include <cassert>
#include <tree.hpp>
#include <iostream>
#include <unordered_map>

class Solution {
public:
    std::unordered_map<long, long> prefix;

    long dfs(TreeNode *root, long cur, long target) {
        if (!root) return 0;
        long ret = 0;
        cur += root->val;
        if (prefix.count(cur - target)) ret = prefix[cur - target];
        prefix[cur]++;
        ret += dfs(root->left, cur, target);
        ret += dfs(root->right, cur, target);
        prefix[cur]--;
        return ret;
    }

    long pathSum(TreeNode *root, long targetSum) {
        prefix[0] = 1;
        return dfs(root, 0, targetSum);
    }
};

int main() {
    Solution sol;
    const std::vector arr = {10, 5, -3, 3, 2, -1, 11, 3, -2, -1, 1};
    constexpr long targetSum = 8;
    TreeNode *root = TreeUtils::arrToTree(arr);
    std::cout << "符合要求的路径数量为：" << sol.pathSum(root, targetSum) << std::endl;
    TreeUtils::freeTree(root);
    return 0;
}