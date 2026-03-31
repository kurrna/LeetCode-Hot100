/*
 * @lc app=leetcode.cn id=54 lang=java
 *
 * [54] 螺旋矩阵
 */

// @lc code=start
import java.util.*;

class Solution {
    public List<Integer> spiralOrder(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;
        List<Integer> res = new ArrayList<>();
        int[][] directions = { 
            {0, 1},     // 右
            {1, 0},     // 下
            {0, -1},    // 左
            {-1, 0}     // 上
        };
        boolean[][] visited = new boolean[m][n];
        int directionIndex = 0;
        int row = 0, col = 0;
        for (int i = 0; i < m * n; i++) {
            res.add(matrix[row][col]);
            visited[row][col] = true;
            int nextRow = row + directions[directionIndex][0];
            int nextCol = col + directions[directionIndex][1];
            // 若遇到边界或遇到走过的格子，转向
            if (nextRow < 0 || nextRow >= m || nextCol < 0 || nextCol >= n || visited[nextRow][nextCol]) {
                directionIndex = (directionIndex + 1) % 4;
                nextRow = row + directions[directionIndex][0];
                nextCol = col + directions[directionIndex][1];
            }
            row = nextRow;
            col = nextCol;
        }
        return res;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[][] matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
        sol.spiralOrder(matrix).stream().forEach(num -> System.out.print(num + " "));
    }
}
// @lc code=end
