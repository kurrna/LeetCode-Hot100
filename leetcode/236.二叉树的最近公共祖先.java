/*
 * @lc app=leetcode.cn id=236 lang=java
 *
 * [236] 二叉树的最近公共祖先
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
import java.util.*;

class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null || root == p || root == q)
            return root;

        Map<Integer, TreeNode> hm = new HashMap<>();
        Set<Integer> visited = new HashSet<>();
        dfs(hm, root, p, q);
        while (p != null) {
            visited.add(p.val);
            p = hm.get(p.val);
        }
        while (q != null) {
            if (visited.contains(q.val)) {
                return q;
            }
            visited.add(q.val);
            q = hm.get(q.val);
        }
        return null;
    }

    private void dfs(Map<Integer, TreeNode> hm, TreeNode root, TreeNode p, TreeNode q) {
        if (root.left != null) {
            hm.put(root.left.val, root);
            if ((root == p && hm.containsKey(q.val)) || (root == q && hm.containsKey(p.val)))
                return;
            dfs(hm, root.left, p, q);
        }
        if (root.right != null) {
            hm.put(root.right.val, root);
            if ((root == p && hm.containsKey(q.val)) || (root == q && hm.containsKey(p.val)))
                return;
            dfs(hm, root.right, p, q);
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var root = new TreeNode(3, new TreeNode(5, new TreeNode(6), new TreeNode(2, new TreeNode(7), new TreeNode(4))),
                new TreeNode(1, new TreeNode(0), new TreeNode(8)));
        System.out.println(sol.lowestCommonAncestor(root, root.left, root.left.right.right).val);
    }
}
// @lc code=end
