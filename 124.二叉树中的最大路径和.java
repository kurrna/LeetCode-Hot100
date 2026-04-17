/*
 * @lc app=leetcode.cn id=124 lang=java
 *
 * [124] 二叉树中的最大路径和
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

    int maxSum = Integer.MIN_VALUE;
    public int maxPathSum(TreeNode root) {
        dfs(root);
        return maxSum;
    }

    public int dfs(TreeNode tn) {
        if (tn == null) return 0;
        int leftSum = Math.max(dfs(tn.left), 0);
        int rightSum = Math.max(dfs(tn.right), 0);
        int rootSum = tn.val + leftSum + rightSum;
        maxSum = Math.max(rootSum, maxSum);
        return tn.val + Math.max(leftSum, rightSum);
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var root = new TreeNode(-10, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
        var minus = new TreeNode(-2, new TreeNode(-1), null);
        System.out.println(sol.maxPathSum(root));
        sol.maxSum = Integer.MIN_VALUE;
        System.out.println(sol.maxPathSum(minus));
    }
}
// @lc code=end

