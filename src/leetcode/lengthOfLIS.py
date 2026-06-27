#
# @lc app=leetcode.cn id=300 lang=python3
#
# [300] 最长递增子序列
#

# @lc code=start
from typing import List

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        """
        最长递增子序列 (LIS)
        
        方法：贪心 + 二分查找 O(n log n)
        tails[i] 表示长度为 i+1 的递增子序列的末尾元素的最小值
        遍历每个数 x，在 tails 中二分查找第一个 >= x 的位置：
          - 找到则替换，降低该长度子序列的"天花板"
          - 没找到（x 比所有 tails 都大）则追加，序列长度 +1
        tails 的长度即为 LIS 长度
        """
        tails = []
        for x in nums:
            # 二分查找第一个 >= x 的位置
            l, r = 0, len(tails)
            while l < r:
                mid = (l + r) // 2
                if tails[mid] >= x:
                    r = mid
                else:
                    l = mid + 1
            if l == len(tails):
                tails.append(x)
            else:
                tails[l] = x
        
        return len(tails)
# @lc code=end

def main():
    sol = Solution()
    nums = [10, 9, 2, 5, 3, 7, 101, 18]
    print(sol.lengthOfLIS(nums))
    
if __name__ == "__main__":
    main()