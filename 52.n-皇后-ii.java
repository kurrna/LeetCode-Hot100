/*
 * @lc app=leetcode.cn id=52 lang=java
 *
 * [52] N 皇后 II
 */

// @lc code=start
class Solution {

    public int totalNQueens(int n) {
        int columns = 0, diagonals1 = 0, diagonals2 = 0;
        return backtrack(n, 0, columns, diagonals1, diagonals2);
    }

    private int backtrack(int n, int row, int columns, int diagonals1, int diagonals2) {
        if (row == n) {
            return 1;
        }
        int count = 0;
        for (int col = 0; col < n; col++) {
            if ((columns & (1 << col)) != 0) {
                continue;
            }
            int diagonal1 = row - col;
            if ((diagonals1 & (1 << diagonal1)) != 0) {
                continue;
            }
            int diagonal2 = row + col;
            if ((diagonals2 & (1 << diagonal2)) != 0) {
                continue;
            }
            columns |= (1 << col);
            diagonals1 |= (1 << diagonal1);
            diagonals2 |= (1 << diagonal2);
            count += backtrack(n, row + 1, columns, diagonals1, diagonals2);
            columns &= ~(1 << col);
            diagonals1 &= ~(1 << diagonal1);
            diagonals2 &= ~(1 << diagonal2);
        }
        return count;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        int n = 4;
        int result = solution.totalNQueens(n);
        System.out.println("Total N-Queens solutions for n = " + n + ": " + result);
    }
}
// @lc code=end

