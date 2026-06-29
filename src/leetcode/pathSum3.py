#
# @lc app=leetcode.cn id=437 lang=python3
#
# [437] 路径总和 III
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
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:
        self.cnt = {0: 1}
        self.t = targetSum
        return self._dfs(root, 0)

    def _dfs(self, node, cur_sum):
        if not node:
            return 0
        cur_sum += node.val
        cnt = self.cnt
        ans = cnt.get(cur_sum - self.t, 0)
        cnt[cur_sum] = cnt.get(cur_sum, 0) + 1
        ans += self._dfs(node.left, cur_sum)
        ans += self._dfs(node.right, cur_sum)
        cnt[cur_sum] -= 1
        return ans


# @lc code=end

def main():
    sol = Solution()
    root = TreeNode(10, TreeNode(5, TreeNode(3, TreeNode(3), TreeNode(-2)), TreeNode(2, None, TreeNode(1))), TreeNode(-3, None, TreeNode(11)))
    print(sol.pathSum(root, 8))
    
if __name__ == "__main__":
    main()
