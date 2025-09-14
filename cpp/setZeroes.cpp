//
// Created by Kurna on 25-9-13.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // 空间复杂度O(m+n)
    void setZeroes(vector<vector<int> > &matrix) {
        int rowFlag = 0, colFlag = 0, colFlags[200] = {0};
        for (auto &vec: matrix) {
            rowFlag = 0;
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] == 0) {
                    rowFlag = 1;
                    colFlag = 1;
                    colFlags[i] = 1;
                }
            }
            if (rowFlag) {
                for (auto &x: vec) {
                    x = 0;
                }
            }
        }
        if (colFlag)
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (colFlags[j]) {
                    for (auto &i: matrix) {
                        i[j] = 0;
                    }
                }
            }
    }
    // 空间复杂度O(1)
    void setZeroesWithLowerRoom(vector<vector<int> > &matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int flag_col0 = 0;
        for (int i = 0; i < m; ++i) {
            if (!matrix[i][0]) {
                flag_col0 = 1;
            }
            for (int j = 1; j < n; ++j) {
                if (!matrix[i][j]) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 1; j < n; ++j) {
                if (!matrix[i][0] || !matrix[0][j]) {
                    matrix[i][j] = 0;
                }
            }
            if (flag_col0) {
                matrix[i][0] = 0;
            }
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int> > matrix = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
    sol.setZeroes(matrix);
    cout << "{";
    for (int j = 0; j < matrix.size(); ++j) {
        cout << "{";
        auto &vec = matrix[j];
        for (int i = 0; i < vec.size(); ++i) {
            cout << vec[i];
            if (i == vec.size() - 1) cout << "}";
            if (i != vec.size() - 1 || j != matrix.size() - 1)
                cout << ", ";
        }
    }
    cout << "}";
    return 0;
}
