//
// Created by Kurna on 25-10-13.
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int uniquePaths(int m, int n) {
        // vector dp(max(m, n), vector<int>(max(m, n), 0));
        // dp[0][0] = 1;
        // for (int i = 1; i < m + n; ++i) {
        //     for (int j = 0; j <= i; ++j) {
        //         if (j >= n || i - j >= m) continue;
        //         dp[j][i - j] = (j > 0 ? dp[j - 1][i - j] : 0) +
        //             (i - j > 0 ? dp[j][i - j - 1] : 0);
        //     }
        // }
        int n1 = m + n - 2, k = min(m - 1, n - 1);
        if (k > n1 || k < 0) return 0;
        long long res = 1;
        for (int i = 1; i <= k; ++i) {
            res = res * (n1 - i + 1) / i;
        }
        return (int)res;
    }
};

class SolutionByDP {
   public:
    // 滚动数组更新：左边与上方之和
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j-1];
            }
        }
        return dp[n-1];
    }
};

int main() {
    Solution sol;
    cout << sol.uniquePaths(3, 7) << endl;
    return 0;
}