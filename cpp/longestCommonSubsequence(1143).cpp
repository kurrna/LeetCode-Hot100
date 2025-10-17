#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.size() < text2.size()) swap(text1, text2);  // 保证 text2 更短，节省空间
        int m = (int)text1.size(), n = (int)text2.size();
        vector<int> dp(n + 1, 0);  // dp[j] 对应前 i 行的状态，j 为 text2 的前缀长度

        for (int i = 1; i <= m; ++i) {
            int prev = 0;  // 保存 dp[j-1] 在上一行的值（即 dp[i-1][j-1]）
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j];  // 暂存当前 dp[j]（即上一行的 dp[i-1][j]）
                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);  // dp[j] 是 dp[i-1][j], dp[j-1] 是 dp[i][j-1]
                }
                prev = temp;
            }
        }
        return dp[n];
    }
};

int main() {
    Solution sol;
    string text1 = "abcde", text2 = "ace";
    cout << sol.longestCommonSubsequence(text1, text2) << endl; // 输出 3
                return 0;
            }