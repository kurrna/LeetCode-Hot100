#
# @lc app=leetcode.cn id=279 lang=python3
#
# [279] 完全平方数
#
import collections
# @lc code=start
class Solution:
    def numSquares(self, n: int) -> int:
        queue = collections.deque([(n, 0)])
        visited = set()
        visited.add(n)
        while queue:
            current, steps = queue.popleft()
            if current == 0:
                return steps
            i = 1
            while i * i <= current:
                next_val = current - i * i
                if next_val not in visited:
                    visited.add(next_val)
                    queue.append((next_val, steps + 1))
                i += 1
                
        return -1

# @lc code=end

def main():
    sol = Solution()
    print(sol.numSquares(13))
    
if __name__ == "__main__":
    main()