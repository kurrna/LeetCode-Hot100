//
// Created by Kurna on 2025/11/14.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 只能使用MSVC编译器编译通过，GCC会报错
class Solution {
private:
    vector<bool> row;
    vector<bool> col;
    vector<bool> l_diag;
    vector<bool> r_diag;

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        row.assign(n, false);
        col.assign(n, false);
        l_diag.assign(2 * n - 1, false);
        r_diag.assign(2 * n - 1, false);
        vector<string> approach(n, "");
        string track;

        auto backtrack = [&](this auto &&self, int rowIndex)->void {
            if (rowIndex == n) {
                ans.push_back(approach);
                return;
            }

            for (int colIndex = 0; colIndex < n; ++colIndex) {
                if (col[colIndex] || l_diag[rowIndex - colIndex + n - 1] || r_diag[rowIndex + colIndex]) {
                    continue;
                }

                // Place the queen
                col[colIndex] = l_diag[rowIndex - colIndex + n - 1] = r_diag[rowIndex + colIndex] = true;
                approach[rowIndex] = string(colIndex, '.') + 'Q' + string(n - colIndex - 1, '.');

                // Recurse
                self(rowIndex + 1);

                // Backtrack
                col[colIndex] = l_diag[rowIndex - colIndex + n - 1] = r_diag[rowIndex + colIndex] = false;
                approach[rowIndex] = "";
            }
        };

        backtrack(0);
        return ans;
    }
};

int main() {
    Solution sol;
    for (auto ans = sol.solveNQueens(9); const auto &vec : ans) {
        for (const auto &s : vec) {
            cout << s << "\n";
        }
        cout << "\n";
    }
    return 0;
}