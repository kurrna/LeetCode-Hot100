//
// Created by Kurna on 25-9-23.
//
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// 动态规划O(n)
class Solution {
    unordered_map<int, int> stairMap;

    void climbStairsHelper(int n) {
        if (n > 2) {
            climbStairsHelper(n - 1);
            stairMap[n] = stairMap[n - 2] + stairMap[n - 1];
        }
    }

public:
    int climbStairs(int n) {
        stairMap[0] = 1, stairMap[1] = 1, stairMap[2] = 2;
        climbStairsHelper(n);
        return stairMap[n];
    }
};

// 齐次线性递推，矩阵快速幂O(k^3*logn)在n较大时更快
class SolutionBy {
public:
    vector<vector<long long> > matrixMultiply(vector<vector<long long>> a, vector<vector<long long>> b) {
        vector res(2, vector<long long>(2));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                res[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return res;
    }

    vector<vector<long long>> matrixPow(vector<vector<long long>> a, int n) {
        vector<vector<long long>> res = {{1, 0}, {0, 1}};
        while (n > 0) {
            if ((n & 1) == 1) {
                res = matrixMultiply(res, a);
            }
            n >>= 1;
            a = matrixMultiply(a, a);
        }
        return res;
    }

    int climbStairs(int n) {
        vector<vector<long long>> res = {{1, 1}, {1, 0}};
        vector<vector<long long>> ret = matrixPow(res, n);
        return ret[0][0];
    }
};

int main() {
    SolutionBy sol;
    auto n = 4;
    cout << sol.climbStairs(n) << endl;
    return 0;
}
