/*
 * @lc app=leetcode.cn id=72 lang=java
 *
 * [72] 编辑距离
 */

// @lc code=start
class Solution {
    // public int minDistance(String word1, String word2) {
    // int m = word1.length(), n = word2.length();
    // int[][] dp = new int[m+1][n+1];
    // if (m == 0) return n;
    // if (n == 0) return m;
    // for (int i = 0; i <= m; i++) {
    // dp[i][0] = i;
    // }
    // for (int j = 0; j <= n; j++) {
    // dp[0][j] = j;
    // }
    // for (int i = 1; i <= m; i++) {
    // for (int j = 1; j <= n; j++) {
    // if (word1.charAt(i-1) == word2.charAt(j-1)) {
    // dp[i][j] = dp[i-1][j-1];
    // } else {
    // dp[i][j] = Math.min(Math.min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]) + 1;
    // }
    // }
    // }
    // return dp[m][n];
    // }

    public int minDistance(String word1, String word2) {
        int m = word1.length(), n = word2.length();
        if (n < m)
            return minDistance(word2, word1);
        if (m == 0)
            return n;
        if (n == 0)
            return m;
        int[] dp = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            dp[i] = i;
        }
        int leftUp = 0, up = 0;
        for (int i = 1; i <= m; i++) {
            leftUp = dp[0];
            dp[0] = i;
            for (int j = 1; j <= n; j++) {
                up = dp[j];
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[j] = leftUp;
                } else {
                    dp[j] = Math.min(Math.min(dp[j-1], up), leftUp) + 1;
                }
                leftUp = up;
            }
        }
        return dp[n];
    }

    public static void main(String[] args) {
        var sol = new Solution();
        System.out.println(sol.minDistance("horse", "ros"));
    }
}
// @lc code=end
