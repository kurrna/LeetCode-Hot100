/*
 * @lc app=leetcode.cn id=98 lang=java
 *
 * [98] 验证二叉搜索树
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
    public boolean isValidBST(TreeNode root) {
        return dfs(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }

    private boolean dfs(TreeNode root, long left, long right) {
        if (root == null) {
            return true;
        }
        if (root.val <= left || root.val >= right) {
            return false;
        }
        return dfs(root.left, left, root.val) && dfs(root.right, root.val, right);
    }

    public static void main(String[] args) {
        var sol = new Solution();
        TreeNode root = new TreeNode(5);
        root.left = new TreeNode(1);
        root.right = new TreeNode(4, new TreeNode(3), new TreeNode(6));
        System.out.println(sol.isValidBST(root));
    }
}
// @lc code=end

