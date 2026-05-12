/*
 * @lc app=leetcode.cn id=198 lang=java
 *
 * [198] 打家劫舍
 */

// @lc code=start
class Solution {
    public int rob(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n+1];
        dp[0] = 0; dp[1] = nums[0];
        for (int i = 2; i <= n; i++) {
            dp[i] = Math.max(dp[i-1], dp[i-2] + nums[i-1]);
        }
        return dp[n];
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {1, 2, 3, 1};
        System.out.println(sol.rob(nums));
    }
}
// @lc code=end

