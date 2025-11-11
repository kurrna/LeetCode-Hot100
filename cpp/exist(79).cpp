//
// Created by Kurna on 2025/11/9.
//
#include <bits/stdc++.h>

class Solution {
public:
    bool exist(std::vector<std::vector<char>>& board, const std::string& word) {
        int m = static_cast<int>(board.size());
        int n = static_cast<int>(board[0].size());
        std::vector visited(m, std::vector(n, false));
        auto backtrack = [&](this auto self, int row, int col, int index) {
            if (index == static_cast<int>(word.size())) {
                return true;
            }
            if (row < 0 || row >= m || col < 0 || col >= n ||
                visited[row][col] || board[row][col] != word[index]) {
                return false;
                }
            visited[row][col] = true;
            bool found = self(row + 1, col, index + 1) ||
                         self(row - 1, col, index + 1) ||
                         self(row, col + 1, index + 1) ||
                         self(row, col - 1, index + 1);
            visited[row][col] = false;
            return found;
        };
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (backtrack(i, j, 0)) return true;

        return false;
    }
};

int main() {
    Solution sol;
    std::vector<std::vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    std::string word = "ABCCED";
    bool ans = sol.exist(board, word);
    std::cout << (ans ? "true" : "false") << std::endl;
    return 0;
}