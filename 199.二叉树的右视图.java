/*
 * @lc app=leetcode.cn id=199 lang=java
 *
 * [199] 二叉树的右视图
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
import java.util.*;

class Solution {
    public List<Integer> rightSideView(TreeNode root) {
        if (root == null) return new ArrayList<>();
        List<Integer> list = new ArrayList<>();
        Queue<TreeNode> queue = new LinkedList<>();
        Queue<TreeNode> next_queue = new LinkedList<>();
        queue.add(root);
        while (!queue.isEmpty()) {
            while (!queue.isEmpty()) {
                var tn = queue.poll();
                if (queue.isEmpty()) {
                    list.add(tn.val);
                }
                if (tn.left != null) {
                    next_queue.add(tn.left);
                }
                if (tn.right != null) {
                    next_queue.add(tn.right);
                }
            }
            queue = next_queue;
            next_queue = new LinkedList<>();
        }
        return list;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        TreeNode root = new TreeNode(1, new TreeNode(2, null, new TreeNode(5)), new TreeNode(3, null, new TreeNode(4)));
        var res = sol.rightSideView(root);
        res.forEach(num -> System.out.print(num + " "));
    }
}
// @lc code=end
