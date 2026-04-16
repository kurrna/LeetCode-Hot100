/*
 * @lc app=leetcode.cn id=114 lang=java
 *
 * [114] 二叉树展开为链表
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
    public void flatten(TreeNode root) {
        if (root == null) {
            return;
        }
        var stack = new Stack<TreeNode>();
        stack.push(root);
        TreeNode prev = null;
        while (!stack.isEmpty()) {
            var node = stack.pop();
            if (prev != null) {
                prev.left = null;
                prev.right = node;
            }
            if (node.right != null) {
                stack.push(node.right);
            }
            if (node.left != null) {
                stack.push(node.left);
            }
            prev = node;
        }
    }

    public static void main(String[] args) {
        var solution = new Solution();
        var root = new TreeNode(1, new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(5, null, new TreeNode(6)));
        solution.flatten(root);
        quickPrint(root);
    }

    private static void quickPrint(TreeNode root) {
        while (root != null) {
            System.out.print(root.val + " ");
            root = root.right;
        }
    }
}
// @lc code=end