//
// Created by Kurna on 25-9-15.
//
#include <iostream>
#include <vector>
using namespace std;

// 从矩阵的右上角或者左下角开始进行搜索，时间复杂度O(m+n)
class Solution {
public:
    bool searchMatrix(vector<vector<int> > matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0, j = n - 1; i <= m - 1 && j >= 0; ) {
            if (matrix[i][j] > target) {
                --j;
            } else if (matrix[i][j] < target) {
                ++i;
            } else {
                return true;
            }
        }
        return false;
    }
};

// 对每一行使用二分查找，O(mlogn)
class BinarySearch {
public:
    bool searchMatrix(vector<vector<int> > matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; ++i) {
            int l = 0, r = n - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (matrix[i][mid] > target) {
                    r = mid - 1;
                } else if (matrix[i][mid] < target) {
                    l = mid + 1;
                } else {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int> > matrix = {
        {1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}
    };
    int target = 5;
    BinarySearch sol;
    // sol.searchMatrix({{-5}}, -5);
    cout << sol.searchMatrix(matrix, 5) << "\n";
    cout << sol.searchMatrix(matrix, 20) << endl;
}
