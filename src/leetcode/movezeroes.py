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
        left, right = 0, 0
        for right in range(len(nums)):
            if nums[right] != 0:
                nums[right], nums[left] = nums[left], nums[right]
                left += 1
        
# @lc code=end

def main():
    sol = Solution()
    nums = [0, 1]
    sol.moveZeroes(nums)
    print(nums)
    
if __name__ == "__main__":
    main()
