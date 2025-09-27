//
// Created by Kurna on 25-9-26.
//
#include <iostream>
#include <vector>
using namespace std;

// dp
class Solution {
public:
    int numSquares(int n) {
        vector dp(n+1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i], dp[i-j*j] + 1);
                if (dp[i] == 1) break;
            }
        }
        return dp[n];
    }
};

#include <queue>
// BFS
class SolutionBFS {
public:
    int numSquares(int n) {
        queue<int> q;
        q.push(0);
        vector cache(n+1, 0);
        cache[0] = 0;
        while (!q.empty()) {
            int val = q.front();
            q.pop();
            if (n == val) return cache[val];
            for (int i = 1; ; ++i) {
                int next = val + i * i;
                if (next > n) break;
                if (cache[next] == 0) {
                    cache[next] = cache[val] + 1;
                    q.push(next);
                    if (next == n) return cache[next];
                }
            }
        }
        return -1;
    }
};

int main() {
    SolutionBFS sol;
    cout << sol.numSquares(12) << endl;
    return 0;
}