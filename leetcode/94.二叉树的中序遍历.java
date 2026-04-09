/*
 * @lc app=leetcode.cn id=94 lang=java
 *
 * [94] 二叉树的中序遍历
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
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        Stack<TreeNode> stk = new Stack<>();
        TreeNode curr = root;
        while (curr != null || !stk.isEmpty()) {
            while (curr != null) {
                stk.push(curr);
                curr = curr.left;
            }
            curr = stk.pop();
            res.add(curr.val);
            curr = curr.right;
        }
        return res;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        TreeNode root = new TreeNode(1);
        root.right = new TreeNode(2);
        root.right.left = new TreeNode(3);
        List<Integer> result = sol.inorderTraversal(root);
        System.out.println(result); // 输出: [1, 3, 2]
    }
}
// @lc code=end

