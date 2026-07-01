#
# @lc app=leetcode.cn id=739 lang=python3
#
# [739] 每日温度
#
from typing import List
# @lc code=start
class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        ans = [0] * len(temperatures)
        stk = []  # 单调递减栈，存储索引
        for i, t in enumerate(temperatures):
            while stk and temperatures[stk[-1]] < t:
                prev_idx = stk.pop()
                ans[prev_idx] = i - prev_idx
            stk.append(i)
        return ans
                
        
# @lc code=end

def main():
    sol = Solution()
    temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
    print(sol.dailyTemperatures(temperatures))
    
if __name__ == "__main__":
    main()