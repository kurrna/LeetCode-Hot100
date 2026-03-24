/*
 * @lc app=leetcode.cn id=37 lang=java
 *
 * [37] 解数独
 */

// @lc code=start
class Solution0 {
    public void solveSudoku(char[][] board) {
        backtrack(board, 0, 0);
    }

    private boolean backtrack(char[][] board, int row, int col) {
        if (col == 9) {
            return backtrack(board, row + 1, 0);
        }
        if (row == 9) {
            return true;
        }
        if (board[row][col] != '.') {
            return backtrack(board, row, col + 1);
        }
        for (char c = '1'; c <= '9'; c++) {
            if (isValid(board, row, col, c)) {
                board[row][col] = c;
                if (backtrack(board, row, col + 1)) {
                    return true;
                }
                board[row][col] = '.';
            }
        }
        return false;
    }

    private boolean isValid(char[][] board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == c) {
                return false;
            }
            if (board[i][col] == c) {
                return false;
            }
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;
            if (board[boxRow][boxCol] == c) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Solution s = new Solution();
        char[][] board = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };
        s.solveSudoku(board);
        // Print the solved board
        for (char[] row : board) {
            for (char c : row) {
                System.out.print(c + " ");
            }
            System.out.println();
        }
    }
}

class Solution {
    public void solveSudoku(char[][] board) {
        backtrack(board);
    }

    // 启发式搜索（MRV）
    private boolean backtrack(char[][] board) {
        int[] minCell = findMinRemainingValuesCell(board);
        if (minCell == null) {
            return true;
        }

        int row = minCell[0];
        int col = minCell[1];

        for (char c = '1'; c <= '9'; c++) {
            if (isValid(board, row, col, c)) {
                board[row][col] = c;
                if (backtrack(board)) {
                    return true;
                }
                // 回溯
                board[row][col] = '.';
            }
        }
        return false;
    }

    private int[] findMinRemainingValuesCell(char[][] board) {
        int minCount = Integer.MAX_VALUE;
        int[] minCell = null;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    int count = countValidNumbers(board, i, j);
                    if (count < minCount) {
                        minCount = count;
                        minCell = new int[]{i, j};
                    }
                }
            }
        }
        return minCell;
    }

    private int countValidNumbers(char[][] board, int row, int col) {
        int count = 0;
        for (char c = '1'; c <= '9'; c++) {
            if (isValid(board, row, col, c)) {
                count++;
            }
        }
        return count;
    }

    private boolean isValid(char[][] board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == c || board[i][col] == c) {
                return false;
            }
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;
            if (board[boxRow][boxCol] == c) {
                return false;
            }
        }
        return true;
    }
}
// @lc code=end

