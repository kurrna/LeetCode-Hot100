#include <iostream>
#include <vector>
#include <unordered_map>
#include <tree.hpp>
using namespace std;

class Solution {
    unordered_map<TreeNode *, int> dp;
    int res = INT_MIN;

public:
    void postOrder(TreeNode *root) {
        if (!root) return;
        if (root->left) postOrder(root->left);
        if (root->right) postOrder(root->right);
        int sum = root->val + max(dp[root->left], 0) + max(dp[root->right], 0);
        if (sum >= res) res = sum;
        dp[root] = root->val + max(max(dp[root->left], 0), max(dp[root->right], 0));
    }

    int maxPathSum(TreeNode *root) {
        if (root == nullptr) return 0;
        dp[nullptr] = 0;
        postOrder(root);
        return res;
    }
};

class SolutionWithoutHM {
public:
    int maxSum = INT_MIN;
    int maxPathSumHelper(TreeNode *root) {
        if (!root) return 0;
        int leftSum = max(maxPathSumHelper(root->left), 0);
        int rightSum = max(maxPathSumHelper(root->right), 0);
        int rootSum = root->val + leftSum + rightSum;
        maxSum = max(rootSum, maxSum);
        return root->val + max(leftSum, rightSum);
    }
    int maxPathSum(TreeNode *root) {
        maxPathSumHelper(root);
        return maxSum;
    }
};

int main() {
    Solution sol;
    vector treeArr = {9,6,-3,INT_MIN,INT_MIN,-6,2,INT_MIN,INT_MIN,2,INT_MIN,-6,-6,-6};
    TreeNode *root = TreeUtils::arrToTree(treeArr);
    cout << sol.maxPathSum(root) << endl;
    return 0;
}
