#
# @lc app=leetcode.cn id=560 lang=python3
#
# [560] 和为 K 的子数组
#
from typing import List
# @lc code=start
class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        ans = 0
        prefix_sum = 0
        prefix_sum_count = {0: 1}  # Initialize with prefix sum 0
        for num in nums:
            prefix_sum += num
            if prefix_sum - k in prefix_sum_count:
                ans += prefix_sum_count[prefix_sum - k]
            prefix_sum_count[prefix_sum] = prefix_sum_count.get(prefix_sum, 0) + 1
        return ans
            
        
# @lc code=end

def main():
    sol = Solution()
    nums = [1, 1, 1]
    k = 2
    print(sol.subarraySum(nums, k))
    
if __name__ == "__main__":
    main()