#
# @lc app=leetcode.cn id=407 lang=python3
#
# [407] 接雨水 II
#
from typing import List
import heapq

# @lc code=start
class Solution:
    def trapRainWater(self, heightMap: List[List[int]]) -> int:
        if not heightMap or not heightMap[0]:
            return 0

        m, n = len(heightMap), len(heightMap[0])
        visited = [[False] * n for _ in range(m)]
        # 最小堆，存储 (高度, 行, 列)
        heap = []
        directions = [[-1, 0], [1, 0], [0, -1], [0, 1]]

        # 将四条边界上的所有单元格加入堆
        for i in range(m):
            for j in range(n):
                if i == 0 or i == m - 1 or j == 0 or j == n - 1:
                    heapq.heappush(heap, (heightMap[i][j], i, j))
                    visited[i][j] = True

        water = 0
        while heap:
            h, i, j = heapq.heappop(heap)
            for di, dj in directions:
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and not visited[ni][nj]:
                    visited[ni][nj] = True
                    # 如果邻居比当前边界高度低，则可以积水
                    if heightMap[ni][nj] < h:
                        water += h - heightMap[ni][nj]
                        heapq.heappush(heap, (h, ni, nj))
                    else:
                        heapq.heappush(heap, (heightMap[ni][nj], ni, nj))

        return water
        
        
# @lc code=end

def main():
    sol = Solution()
    heightMap = [[1, 4, 3, 1, 3, 2], [3, 2, 1, 3, 2,4], [2, 3, 3, 2, 3, 1]]
    print(sol.trapRainWater(heightMap))
    
if __name__ == "__main__":
    main()