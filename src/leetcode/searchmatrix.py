#
# @lc app=leetcode.cn id=240 lang=python3
#
# [240] 搜索二维矩阵 II
#
from typing import List

# @lc code=start
class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        row = len(matrix)
        if row == 0:
            return False
        col = len(matrix[0])
        if col == 0:
            return False
        for i in range(row):
            if matrix[i][0] <= target <= matrix[i][col - 1]:
                left, right = 0, col - 1
                while left <= right:
                    mid = (left + right) // 2
                    if matrix[i][mid] == target:
                        return True
                    elif matrix[i][mid] > target:
                        right = mid - 1
                    else:
                        left = mid + 1
        return False
# @lc code=end

def main():
    solution = Solution()
    matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]
    target = 5
    print(solution.searchMatrix(matrix, target))
    
if __name__ == "__main__":
    main()