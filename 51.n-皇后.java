/*
 * @lc app=leetcode.cn id=51 lang=java
 *
 * [51] N 皇后
 */

// @lc code=start
import java.util.*;
class Solution {
    public List<List<String>> solveNQueens(int n) {
        char[][] board = new char[n][n];
        for (int i = 0; i < n; i++) {
            Arrays.fill(board[i], '.');
        }
        List<List<String>> result = new ArrayList<>();
        backtrack(board, 0, n, result);
        return result;
    }

    private void backtrack(char[][] board, int row, int n, List<List<String>> result) {
        if (row == n) {
            result.add(Arrays.stream(board).map(String::new).toList());
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid(board, row, col, n)) {
                board[row][col] = 'Q';
                backtrack(board, row + 1, n, result);
                board[row][col] = '.';
            }
        }
    }

    private boolean isValid(char[][] board, int row, int col, int n) {
        for (int i = 0; i < n; i++) {
            if (board[row][i] == 'Q' || board[i][col] == 'Q') {
                return false;
            }
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }
        for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        var res = sol.solveNQueens(4);
        for (var ss : res) {
            for (var s : ss) {
                System.out.println(s);
            }
            System.out.println();
        }
    }
}
// @lc code=end

