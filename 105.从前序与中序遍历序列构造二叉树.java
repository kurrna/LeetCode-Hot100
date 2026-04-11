/*
 * @lc app=leetcode.cn id=105 lang=java
 *
 * [105] 从前序与中序遍历序列构造二叉树
 */

// @lc code=start
/**
 * Definition for a binary tree node. public class TreeNode { int val; TreeNode
 * left; TreeNode right; TreeNode() {} TreeNode(int val) { this.val = val; }
 * TreeNode(int val, TreeNode left, TreeNode right) { this.val = val; this.left
 * = left; this.right = right; } }
 */
class Solution {
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        TreeNode root = buildTree(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
        return root;
    }

    private TreeNode buildTree(int[] preorder, int preorderLeft, int preorderRight, int[] inorder, int inorderLeft, int inorderRight) {
        if (preorderLeft > preorderRight || inorderLeft > inorderRight) {
            return null;
        }
        int rootVal = preorder[preorderLeft];
        int rootIdxInInorder = 0;
        for (int i = inorderLeft; i <= inorderRight; i++) {
            if (rootVal == inorder[i]) {
                rootIdxInInorder = i;
                break;
            }
        }
        int leftChildSize = rootIdxInInorder - inorderLeft;
        TreeNode root = new TreeNode(rootVal, 
            buildTree(preorder, preorderLeft + 1, preorderLeft + leftChildSize, inorder, inorderLeft, rootIdxInInorder - 1), 
            buildTree(preorder, preorderLeft + leftChildSize + 1, preorderRight, inorder, rootIdxInInorder + 1, inorderRight)
        );
        return root;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] preorder = { 3, 9, 20, 15, 7 }, inorder = { 9, 3, 15, 20, 7 };
        var tn = sol.buildTree(preorder, inorder);
        quickPrint(tn);
    }

    private static void quickPrint(TreeNode root) {
        if (root == null) {
            return;
        }
        System.out.print(root.val + " ");
        quickPrint(root.left);
        quickPrint(root.right);
    }
}
// @lc code=end
