#
# @lc app=leetcode.cn id=287 lang=python3
#
# [287] 寻找重复数
#
from typing import List
# @lc code=start
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow = fast = nums[0]
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break
        slow = nums[0]
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        return slow
        
# @lc code=end
def main():
    sol = Solution()
    list = [1, 2, 3, 3, 5, 4]
    print(sol.findDuplicate(list))
    
if __name__ == "__main__":
    main()
