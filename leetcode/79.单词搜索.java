/*
 * @lc app=leetcode.cn id=79 lang=java
 *
 * [79] 单词搜索
 */

// @lc code=start
class Solution {
    public boolean exist(char[][] board, String word) {
        boolean[][] visited = new boolean[board.length][board[0].length];
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                if (dfs(board, word, visited, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean dfs(char[][] board, String word, boolean[][] visited, int i, int j, int index) {
        if (index == word.length()) {
            return true;
        }
        if (i < 0 || i >= board.length || j < 0 || j >= board[0].length || visited[i][j] || board[i][j] != word.charAt(index)) {
            return false;
        }
        visited[i][j] = true;
        boolean found = dfs(board, word, visited, i + 1, j, index + 1) ||
                        dfs(board, word, visited, i - 1, j, index + 1) ||
                        dfs(board, word, visited, i, j + 1, index + 1) ||
                        dfs(board, word, visited, i, j - 1, index + 1);
        visited[i][j] = false; // 回溯
        return found;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        char[][] board = {
            {'A','B','C','E'},
            {'S','F','C','S'},
            {'A','D','E','E'}
        };
        String word = "ABCCED";
        boolean result = solution.exist(board, word);
        System.out.println(result); // 输出: true
    }
}
// @lc code=end

