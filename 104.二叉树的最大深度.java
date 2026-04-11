/*
 * @lc app=leetcode.cn id=104 lang=java
 *
 * [104] 二叉树的最大深度
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public int maxDepth(TreeNode root) {
        if (root == null) return 0;
        int[] depth = {1};
        dfs(root, depth, 0);
        return depth[0];
    }

    private void dfs(TreeNode tn, int[] depth, int level) {
        if (tn == null) return;
        if (depth[0] == level) depth[0]++;
        dfs(tn.left, depth, level + 1);
        dfs(tn.right, depth, level + 1);
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var res = sol.maxDepth(new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7))));
        System.out.println(res);
    }
}
// @lc code=end

