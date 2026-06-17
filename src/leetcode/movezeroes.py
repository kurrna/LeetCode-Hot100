#
# @lc app=leetcode.cn id=283 lang=python3
#
# [283] 移动零
#
from typing import List

# @lc code=start
class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        slow, fast = 0, 0
        while fast < len(nums):
            while fast < len(nums) and nums[fast] == 0:
                fast += 1
            nums[slow] = nums[fast]
            slow += 1
            fast += 1
        while slow < len(nums):
            nums[slow] = 0
            slow += 1
        
# @lc code=end

def main():
    sol = Solution()
    nums = [0, 1, 0, 3, 12]
    sol.moveZeroes(nums)
    print(nums)
    
if __name__ == "__main__":
    main()
