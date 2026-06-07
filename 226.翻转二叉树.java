/*
 * @lc app=leetcode.cn id=226 lang=java
 *
 * [226] 翻转二叉树
 */

// @lc code=start
/**
 * Definition for a binary tree node. public class TreeNode { int val; TreeNode
 * left; TreeNode right; TreeNode() {} TreeNode(int val) { this.val = val; }
 * TreeNode(int val, TreeNode left, TreeNode right) { this.val = val; this.left
 * = left; this.right = right; } }
 */
class Solution {
    public TreeNode invertTree(TreeNode root) {
        if (root == null)
            return null;

        // ======= Morris遍历核心思想 =======
        // 使用虚拟节点，便于统一处理（包括root节点）
        TreeNode dummy = new TreeNode(-1, root, null);
        TreeNode cur = dummy;

        while (cur != null) {
            if (cur.left == null) {
                // 无左子树，进入右子树
                cur = cur.right;
            } else {
                // 有左子树：找左子树的最右节点
                TreeNode mostRight = cur.left;
                while (mostRight.right != null && mostRight.right != cur) {
                    mostRight = mostRight.right;
                }

                if (mostRight.right == null) {
                    // 【第1次来】建立"线索" - 从最右节点连回cur
                    // 这样可以实现从左子树返回时回到cur
                    mostRight.right = cur;
                    cur = cur.left;
                } else {
                    // 【第2次来】左子树已处理完
                    // 现在处理翻转逻辑
                    mostRight.right = null;  // 拆除线索
                    reverseAndSwap(cur.left, mostRight);
                    cur = cur.right;  // 进入右子树
                }
            }
        }

        return root;
    }

    // 翻转并交换：从from到to的路径
    private void reverseAndSwap(TreeNode from, TreeNode to) {
        // Step1: 反转右指针链（from→...→to变成to→...→from）
        reverseRightEdge(from, to);

        // Step2: 一边恢复指针，一边交换每个节点的左右孩子
        TreeNode prev = null;
        TreeNode cur = to;

        while (true) {
            TreeNode next = cur.right;
            cur.right = prev;  // 恢复right指针

            // 交换左右孩子
            TreeNode temp = cur.left;
            cur.left = cur.right;
            cur.right = temp;

            if (cur == from)
                break;

            prev = cur;
            cur = next;
        }
    }

    private void reverseRightEdge(TreeNode from, TreeNode to) {
        TreeNode prev = null;
        TreeNode cur = from;

        while (prev != to) {
            TreeNode next = cur.right;
            cur.right = prev;
            prev = cur;
            cur = next;
        }
    }

    public static void main(String[] args) {
        var sol = new Solution();
        var root = new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)),
                new TreeNode(7, new TreeNode(6), new TreeNode(9)));
        var res = sol.invertTree(root);
        printTreeNode(res);
    }

    private static void printTreeNode(TreeNode tn) {
        if (tn == null)
            return;
        System.out.print(tn.val + " ");
        printTreeNode(tn.left);
        printTreeNode(tn.right);
    }
}
// @lc code=end
