/*
 * @lc app=leetcode.cn id=70 lang=java
 *
 * [70] 爬楼梯
 */

// @lc code=start
class Solution {
    public int climbStairs(int n) {
        int[] dp = new int[n];
        dp[0] = 1; 
        if (n == 1) return 1;
        dp[1] = 2;
        for (int i = 2; i < n; i++) {
            dp[i] = dp[i-2] + dp[i-1];
        }
        return dp[n-1];
    }

    public static void main(String[] args) {
        var sol = new Solution();
        System.out.println(sol.climbStairs(4));
    }
}
// @lc code=end

