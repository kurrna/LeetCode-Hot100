//
// Created by Kurna on 25-7-29.
//
#include <tree.hpp>
#include <iostream>

class Solution {
public:
    int maxPathSum(TreeNode *root) {
        // 涉及动态规划，之后再做
        return -1;
    }
};

int main() {
    Solution sol;
    const std::vector arr = {1, 2, 3};
    TreeNode *root = TreeUtils::arrToTree(arr);
    std::cout << sol.maxPathSum(root) << std::endl;
    return 0;
}
