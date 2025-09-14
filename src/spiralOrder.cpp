// 2025.9.14
#include <iostream>
#include <vector>
using namespace std;

// 模拟
class Solution {
public:
    vector<vector<int> > mat;
    int m{}, n{};

    enum direction {
        RIGHT, DOWN, LEFT, UP
    };

    void spiral(vector<int> &res, direction d, int cnt_r, int cnt_d, int cnt_l, int cnt_u) {
        if (res.size() == res.capacity()) return;
        switch (d) {
            case RIGHT:
                for (int i = cnt_u; i < n - cnt_d; ++i) {
                    res.push_back(mat[cnt_r][i]);
                }
                spiral(res, DOWN, cnt_r + 1, cnt_d, cnt_l, cnt_u);
                break;
            case DOWN:
                for (int j = cnt_r; j < m - cnt_l; ++j) {
                    res.push_back(mat[j][n - cnt_d - 1]);
                }
                spiral(res, LEFT, cnt_r, cnt_d + 1, cnt_l, cnt_u);
                break;
            case LEFT:
                for (int i = n - cnt_d - 1; i >= cnt_u; --i) {
                    res.push_back(mat[m - cnt_l - 1][i]);
                }
                spiral(res, UP, cnt_r, cnt_d, cnt_l + 1, cnt_u);
                break;
            case UP:
                for (int j = m - cnt_l - 1; j >= cnt_r; --j) {
                    res.push_back(mat[j][cnt_u]);
                }
                spiral(res, RIGHT, cnt_r, cnt_d, cnt_l, cnt_u + 1);
                break;
            default:
                break;
        }
    }

    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        mat = matrix;
        m = matrix.size();
        n = matrix[0].size();
        vector<int> res;
        res.reserve(n * m);
        spiral(res, RIGHT, 0, 0, 0, 0);
        return res;
    }
};

// simulate by layer
class SolutionByLayer {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return {};
        int rows = matrix.size(), columns = matrix[0].size();
        vector<int> order;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; ++column) {
                order.push_back(matrix[top][column]);
            }
            for (int row = top + 1; row <= bottom; ++row) {
                order.push_back(matrix[row][right]);
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    order.push_back(matrix[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    order.push_back(matrix[row][left]);
                }
            }
            left++, right--, top++, bottom--;
        }
        return order;
    }
};

int main() {
    SolutionByLayer sol;
    vector<vector<int> > matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto res = sol.spiralOrder(matrix);
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i];
        if (i != res.size() - 1) cout << ", ";
    }
    return 0;
}
