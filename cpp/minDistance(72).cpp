#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int minDistance(string word1, string word2) {
        /*int m = static_cast<int>(word1.length()), n = static_cast<int>(word2.length());
        word1 = " " + word1, word2 = " " + word2;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i] == word2[j]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
            }
        }
        return dp[m][n];*/
        // 优化空间复杂度O(min(m, n))
        if (word1.size() < word2.size()) swap(word1, word2);
        int m = word1.size(), n = word2.size();
        word1 = " " + word1, word2 = " " + word2;
        vector<int> dp(n + 1, 0);
        for (int j = 1; j <= n; j++) {
            dp[j] = j;
        }
        for (int i = 1; i <= m; i++) {
            int prev = dp[0];  // dp[i-1][j-1]
            dp[0] = i;
            for (int j = 1; j <= n; j++) {
                int temp = dp[j];  // dp[i-1][j]
                if (word1[i] == word2[j]) {
                    dp[j] = prev;
                } else {
                    dp[j] = min({dp[j - 1], prev, temp}) + 1;
                }
                prev = temp;
            }
        }
        return dp[n];
    }
};

int main() {
    Solution sol;
    auto s1 = "horse", s2 = "ros";
    cout << sol.minDistance(s1, s2) << endl;
    return 0;
}