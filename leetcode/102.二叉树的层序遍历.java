/*
 * @lc app=leetcode.cn id=102 lang=java
 *
 * [102] 二叉树的层序遍历
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
    // public List<List<Integer>> levelOrder(TreeNode root) {
    //     if (root == null) {
    //         return new ArrayList<>();
    //     }
    //     List<List<Integer>> res = new ArrayList<>();
    //     Queue<TreeNode> q = new LinkedList<>();
    //     q.add(root);
    //     while (!q.isEmpty()) {
    //         Queue<TreeNode> next_q = new LinkedList<>();
    //         res.add(new ArrayList<>(q.stream().map(tn -> tn.val).toList()));
    //         while (!q.isEmpty()) {
    //             var tn = q.poll();
    //             if (tn.left != null) {
    //                 next_q.add(tn.left);
    //             }
    //             if (tn.right != null) {
    //                 next_q.add(tn.right);
    //             }
    //         }
    //         q = next_q;
    //     }
    //     return res;
    // }

    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        dfs(root, res, 0);
        return res;
    }

    private void dfs(TreeNode tn, List<List<Integer>> res, int level) {
        if (tn == null) return;
        if (res.size() == level) {
            res.add(level, new ArrayList<>());
        }
        res.get(level).add(tn.val);
        dfs(tn.left, res, level + 1);
        dfs(tn.right, res, level + 1);
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var root = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
        var res = sol.levelOrder(root);
        for (var list : res) {
            list.forEach(num -> System.out.print(num + " "));
            System.out.println();
        }
    }
}
// @lc code=end
