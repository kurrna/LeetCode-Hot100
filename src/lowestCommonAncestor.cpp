#include <iostream>
#include <tree.hpp>
#include <unordered_map>

class Solution {
public:
    // dfs
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (!root || root->val == p->val || root->val == q->val) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        return left == nullptr ? right : (right == nullptr ? left : root);
    }

    // hashmap
    // std::unordered_map<int, TreeNode *> hm;
    // std::unordered_map<int, bool> vis;
    // void dfs(TreeNode *root) {
    //     if (root->left) {
    //         hm[root->left->val] = root;
    //         dfs(root->left);
    //     }
    //     if (root->right) {
    //         hm[root->right->val] = root;
    //         dfs(root->right);
    //     }
    // }
    // TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    //     hm[root->val] = nullptr;
    //     dfs(root);
    //     while (p) {
    //         vis[p->val] = true;
    //         p = hm[p->val];
    //     }
    //     while (q != nullptr) {
    //         if (vis[q->val]) return q;
    //         q = hm[q->val];
    //     }
    //     return nullptr;
    // }
};

int main() {
    Solution sol;
    std::vector arr = {3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
    TreeNode *root = TreeUtils::arrToTree(arr);
    std::cout << sol.lowestCommonAncestor(root, root->left, root->right)->val << std::endl;
    return 0;
}
