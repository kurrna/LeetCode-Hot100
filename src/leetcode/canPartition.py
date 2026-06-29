#
# @lc app=leetcode.cn id=416 lang=python3
#
# [416] 分割等和子集
#
from typing import List
# @lc code=start
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        sum = 0
        for num in nums:
            sum += num
        if sum % 2 != 0:
            return False
        target = sum // 2
        dp = [False] * (target + 1)
        dp[0] = True
        for num in nums:
            for i in range(target, num - 1, -1):
                dp[i] = dp[i] or dp[i - num]
            if dp[target]:
                return True
        
        return dp[target]
                
        
# @lc code=end

def main():
    sol = Solution()
    nums = [1, 5, 11, 5]
    print(sol.canPartition(nums))
    
if __name__ == "__main__":
    main()