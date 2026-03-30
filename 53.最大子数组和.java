/*
 * @lc app=leetcode.cn id=53 lang=java
 *
 * [53] 最大子数组和
 */

// @lc code=start
class Solution {
    int[] dp;

    public int maxSubArray(int[] nums) {
        int pre = 0;
        int maxSum = -Integer.MAX_VALUE;
        for (int i = 0; i < nums.length; i++) {
            pre = Math.max(pre + nums[i], nums[i]);
            maxSum = Math.max(maxSum, pre);
        }
        return maxSum;
    }

    public static void main(String[] args) {
        var sol = new Solution();
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        System.out.println(sol.maxSubArray(nums));
    }
}
// @lc code=end

