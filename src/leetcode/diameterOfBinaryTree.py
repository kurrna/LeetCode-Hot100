#
# @lc app=leetcode.cn id=543 lang=python3
#
# [543] 二叉树的直径
#
from leetcode.treeNode import TreeNode
from typing import Optional
# @lc code=start
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        max_diameter = 0

        def dfs(node: Optional[TreeNode]) -> int:
            """返回 node 的高度，同时更新全局最大直径"""
            nonlocal max_diameter
            if not node:
                return 0

            left_height = dfs(node.left)
            right_height = dfs(node.right)

            # 经过当前节点的路径长度 = 左子树高度 + 右子树高度
            max_diameter = max(max_diameter, left_height + right_height)

            # 返回当前节点的高度
            return 1 + max(left_height, right_height)

        dfs(root)
        return max_diameter
        
# @lc code=end
def main():
    sol = Solution()
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    print(sol.diameterOfBinaryTree(root))
    
if __name__ == "__main__":
    main()
