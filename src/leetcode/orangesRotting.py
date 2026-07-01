#
# @lc app=leetcode.cn id=994 lang=python3
#
# [994] 腐烂的橘子
#
from collections import deque
from typing import List

# @lc code=start
class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        directions = [[-1, 0], [0, -1], [1, 0], [0, 1]]
        m, n = len(grid), len(grid[0])
        q = deque()
        fresh = 0

        # 1. 将所有初始腐烂橘子入队，同时统计新鲜橘子数
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 2:
                    q.append((i, j))
                elif grid[i][j] == 1:
                    fresh += 1

        # 如果没有新鲜橘子，直接返回 0
        if fresh == 0:
            return 0

        minutes = 0
        # 2. 多源 BFS 层序遍历
        while q:
            # 当前层的所有腐烂橘子同时扩散（代表 1 分钟）
            for _ in range(len(q)):
                x, y = q.popleft()
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1:
                        # 新鲜橘子被感染
                        grid[nx][ny] = 2
                        q.append((nx, ny))
                        fresh -= 1
            minutes += 1

        # 3. 如果还有新鲜橘子无法被感染，返回 -1
        return -1 if fresh > 0 else minutes - 1

# @lc code=end

def main():
    sol = Solution()
    grid = [[2, 1, 1], [1, 1, 0], [0, 1, 1]]
    print(sol.orangesRotting(grid))
    
if __name__ == "__main__":
    main()