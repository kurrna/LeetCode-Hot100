//
// Created by Kurna on 25-9-14.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 先转置再反转
class SolutionBySwapAndReverse {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

// 原地旋转
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = temp;
            }
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int> > matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    sol.rotate(matrix);
    cout << "{";
    for (int i = 0; i < matrix.size(); ++i) {
        cout << "{";
        for (int j = 0; j < matrix.size(); ++j) {
            cout << matrix[i][j];
            if (j != matrix.size() - 1) cout << ", ";
        }
        cout << "}";
        if (i != matrix.size() - 1) cout << ", ";
    }
    cout << "}";
}
