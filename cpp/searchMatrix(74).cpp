//
// Created by Kurna on 25-9-17.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        // 先找第一列
        int l_col0 = 0, r_col0 = m - 1;
        while (l_col0 <= r_col0) {
            int mid = (r_col0 - l_col0) / 2 + l_col0;
            if (matrix[mid][0] < target) {
                l_col0 = mid + 1;
            } else if (matrix[mid][0] > target) {
                r_col0 = mid - 1;
            } else {
                return true;
            }
        }
        // 再在对应行中找
        int row = max(r_col0, 0);
        int l_row = 0, r_row = n - 1;
        while (l_row <= r_row) {
            int mid = (r_row - l_row) / 2 + l_row;
            if (matrix[row][mid] < target) {
                l_row = mid + 1;
            } else if (matrix[row][mid] > target) {
                r_row = mid - 1;
            } else {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution sol;
    // vector<vector<int> > matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    vector<vector<int> > matrix = {{1}};
    cout << sol.searchMatrix(matrix, 0) << endl;
    return 0;
}
