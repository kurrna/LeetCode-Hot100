//
// Created by Kurna on 25-9-27.
//
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

class SolutionBFS {
public:
    int coinChange(vector<int> &coins, int amount) {
        queue<int> q;
        q.push(0);
        vector visited(amount + 1, 0), cache(amount + 1, INT_MAX);
        cache[0] = 0;
        while (!q.empty()) {
            int val = q.front();
            if (val == amount) return cache[val];
            q.pop();
            if (!visited[val]) {
                int count = cache[val] + 1;
                for (int coin: coins) {
                    int nextVal = val + coin;
                    if (nextVal <= amount && cache[nextVal] == INT_MAX) {
                        q.push(nextVal);
                        cache[nextVal] = count;
                        if (nextVal == amount) return count;
                    }
                }
            }
            visited[val] = 1;
        }
        return -1;
    }
};

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for(int coin : coins) {
            for(int j = coin; j <= amount; j++) {
                if(dp[j - coin] < INT_MAX) dp[j] = min(dp[j], dp[j - coin] + 1);
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};

int main() {
    Solution sol;
    vector coins = {2};
    int amount = 3;
    cout << sol.coinChange(coins, amount) << endl;
    return 0;
}
